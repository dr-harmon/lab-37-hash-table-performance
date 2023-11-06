#include "hashtable_builder.h"
#include "csv.h"

using namespace std;

void addPopularityData(OpenHashMap<string,int>& hashtable)
{
    io::CSVReader<2> in(POPULARITY_CSV_PATH);
    in.read_header(io::ignore_extra_column, "url", "shares");
    string url;
    int shares;
    while (in.read_row(url, shares)) {
        hashtable.put(url, shares);
    }
}
