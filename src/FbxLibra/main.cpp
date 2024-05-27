#include <args-parser/all.hpp>

using namespace Args;

int main(int argc, char ** argv) {
    try {
        CmdLine cmd(argc, argv, CmdLine::CommandIsRequired );
        Command check(SL("check"), ValueOptions::ManyValues, false);
        check.setDescription(SL("Check the fbx."));

        Arg fbx('f', SL("fbx"), true, true);
        check.addArg(&fbx);

        Command create(SL("create"), ValueOptions::ManyValues, false);
        create.addArg(&fbx);

        Help help;
        help.setAppDescription(SL("help"));
        help.setExecutable(argv[0]);

        cmd.addArg(&check);
        cmd.addArg(&create);
        cmd.addArg(help);

        cmd.parse();

        if (cmd.isDefined("check")){
            for (const auto & value : cmd.values("check")){
                outStream() << value << "\n";
            }
            outStream() << cmd.value("-f") << "\n";
        } else if (cmd.isDefined("create")){
            for (const auto & value : cmd.values("create")){
                outStream() << value << "\n";
            }
            outStream() << cmd.value("-f") << "\n";
        }
    }
    catch (const HelpHasBeenPrintedException &){
        return 0;
    }
    catch (const BaseException & e){
        outStream() << e.desc() << "\n";
        return 1;
    }
    return 0;
}