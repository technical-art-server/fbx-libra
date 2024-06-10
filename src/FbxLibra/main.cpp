#include <args-parser/all.hpp>
#include <memory>

#include "FlatBufferLoader.h"
#include "FBXLibra.h"
#include "CounterWeight/HierarchyCounterWeight.h"
#include <magic_enum/magic_enum.hpp>

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
            FBXLibraClient libraClient;

            for (const auto & value : cmd.values("check")){
                int ext_pos = value.find_last_of('.');
                if (ext_pos == std::string::npos){
                    throw BaseException("Invalid file path.");
                }
                std::string ext = value.substr(ext_pos,value.size()-ext_pos);
                // TODO: ここはファクトリークラスにする必要がある
                EmptyCounterWeight* weight;
                EmptyCounterWeight* fbx_weight;
                flatbuffers::FlatBufferBuilder builder(1024);

                if (ext == ".hcw"){
                    weight = new HierarchyCounterWeight(value.c_str());
                    fbx_weight = new HierarchyCounterWeight();
                    fbx_weight->Convert(builder, cmd.value("-f"));
                }else{
                    throw BaseException("Invalid file extension.");
                }

                std::cout << "weight: " << value << std::endl;
                std::cout << "fbx path: " << cmd.value("-f") << std::endl;
                Status result = libraClient.Weigh<EmptyCounterWeight, HierarchyCounterWeight>(weight, fbx_weight);
                if (result == Status::SUCCESS){
                    std::cout << "\033[32m";
                } else{
                    std::cout << "\033[31m";
                }
                std::cout << "Hierarchy: " << magic_enum::enum_name(result) << std::endl;

                delete weight;
                delete fbx_weight;
                builder.Clear();
            }
        } else if (cmd.isDefined("create")){
            for (const auto & value : cmd.values("create")){
                std::cout << value << std::endl;
            }
            std::cout << cmd.value("-f") << std::endl;
        }
    }
    catch (const HelpHasBeenPrintedException &){
        return 0;
    }
    catch (const BaseException & e){
        std::cout << e.desc() << std::endl;
        return 1;
    }
    return 0;
}