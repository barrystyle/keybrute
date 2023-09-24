#include <db.h>
#include <key.h>

#include <unistd.h>
#include <string.h>

#include <iostream>
#include <thread>
#include <vector>
#include <cstdio>

#define MAX_THREADS 4
uint32_t progress[MAX_THREADS];
const std::string& in_file = "addrlist.txt";

void debugprint(unsigned char* buf, int len)
{
    for (int i=0; i<len; i++) {
        printf("%02hhx", buf[i]);
    }
    printf("\n");
}

void print_progress()
{
	uint32_t lastprogress[MAX_THREADS];
	for (int i=0; i<MAX_THREADS; i++) {
		lastprogress[i] = 0;
	}

	while (true)
	{
		for (int i=0; i<MAX_THREADS; i++) {
			uint32_t work = (progress[i]-lastprogress[i]) * 12;
			if (work < 0) work = 0;
			printf("%d:%08x (%d/min) ", i, progress[i], work);
			lastprogress[i] = progress[i];
		}
		printf("\n");
		sleep(5);
	}
}

void worker_thread(uint32_t thr_id)
{
    printf("thread %d launched\n", thr_id);

    static secp256k1_context* ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN);

    unsigned char pk[32];
    random_privkey(pk);
    //debugprint(pk, 32);

    std::vector<unsigned char> pkh;

    uint32_t octet{0};
    for (uint32_t i=0; i<std::numeric_limits<uint32_t>::max(); i++) {
        octet = i;
        progress[thr_id] = i;

        memcpy(pk, &octet, 4);
        //debugprint(pk, 32);

        priv_to_public(ctx, pk, (unsigned char*)&pkh);
        //debugprint((unsigned char*)&pkh, 20);

        if (is_in_db((unsigned char*)&pkh)) {
            printf("FOUND!! ");
            debugprint(pk, 32);
        }
    }

    printf("thread %d completed\n", thr_id);
}

int main()
{
    initdb(in_file);

    int threads = MAX_THREADS;

    std::vector<std::thread> workers;
    for (int i=0; i<threads; i++) {
         workers.push_back(std::thread(&worker_thread, i));
    }

    workers.push_back(std::thread(&print_progress));

    for (int i=0; i<threads+1; i++) {
         workers.at(i).join();
    }

    return 1;
}
