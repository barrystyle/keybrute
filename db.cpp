#include <db.h>

#define DEBUG 0

std::vector<address_t> addresses[256][256];

static uint64_t get_file_lines(const std::string& in_file)
{
    std::ifstream file(in_file.c_str());

    std::string line;
    uint64_t max_entries{0};
    while (std::getline(file, line)) {
        ++max_entries;
    }

    return max_entries;
}

void initdb(const std::string& in_file)
{
    std::ifstream file(in_file.c_str());

    std::string line;
    uint64_t entries{0}, max_entries{0};
    max_entries = get_file_lines(in_file);

    printf("loading %d addresses..\n", max_entries);

    while (std::getline(file, line)) {
        address_t entry;
        // only decode legacy (1) addresses
        if (line.c_str()[0] != '1') {
            continue;
        }
        // skip invalid addresses
        if (!DecodeBase58(line.c_str(), entry.pubkeyhash)) {
            continue;
        }
        ++entries;
        addresses[entry.pubkeyhash[4]][entry.pubkeyhash[8]].push_back(entry);
    }

    printf("loaded %d suitable addresses (%.2f%)..\n", entries, (float) entries / max_entries * 100);
}

bool is_in_db(unsigned char* pkh)
{
    int hit;
    bool found;

    found = false;
    for (auto& l : addresses[pkh[4]][pkh[8]]) {
        hit = 0;
        address_t match = l;
        for (int j=0; j<20; j++) {
            if (match.pubkeyhash[j] != pkh[j]) {
                break;
            }
            ++hit;
        }
        if (hit == 20) {
            return true;
        }
    }
    return false;
}
