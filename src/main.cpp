#include "filehandler.hpp"
#include "log.hpp"

#include <string>
#include <vector>

int main() {
    mugg::Filehandler filehandler;
    filehandler.AppendStringToFile("bajskorv.txt", "\ndet här är en sträng");

	return 0;
}
