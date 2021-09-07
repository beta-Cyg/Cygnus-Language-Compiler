#include<string>
#include<iostream>
#include<cstdlib>
#include<algorithm>
#include"core/grammar_tree.h"
#include"core/ir.h"

std::string no_suffix(std::string input_value){
	std::reverse(input_value.begin(),input_value.end());
	input_value.erase(0,input_value.find(".")+1);
	std::reverse(input_value.begin(),input_value.end());
	return input_value;
}

void echo(const std::string& value,const std::string file_name){
	std::ofstream out(file_name);
	out<<value;
	out.close();
}

int main(int argc,char** args){
	std::string Args[argc];
	for(unsigned long long i=0;i<argc,++i)
		Args[i]=args[i];
	switch(argc){
	case 1:
		std::cout<<"No input file."<<std::endl;
		break;
	case 2:{
		cyg::grammar_tree::g_tree files_g_tree;
		std::string files_name;
		for(int i=1;i<argc;++i){
			files_g_tree=cyg::grammar_tree::parse(Args[i]);
			echo(
				cyg::llvm::to_ir_code(giles_g_tree),
				files_name=no_suffix(Args[i])+".ir"
			    );
			system(("llc "+files_name).c_str());
		}
		break;
		}
	default:
	       break;//todo finish option parser.
	}

	return 0;
}
