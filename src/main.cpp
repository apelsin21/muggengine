#include <string>
#include <vector>

#include "filehandler.hpp"
#include "log.hpp"
#include "file.hpp"
#include "shader.hpp"

int main() {
    mugg::WriteToLog(mugg::INFO, "this informational message won't be printed");
    mugg::WriteToLog(mugg::DEBUG, "this debug message won't show up");
    mugg::WriteToLog(mugg::WARNING, "this is a warning");
    mugg::WriteToLog(mugg::ERROR, "this is an error");
    mugg::WriteToLog(mugg::FATAL_ERROR, "this is a fatal error, omg");

    mugg::Filehandler filehandler;
    mugg::File file = filehandler.GetFileFromPath("log.txt");

    filehandler.WriteFileToPath(file, "logbackup.txt");

	return 0;
}
