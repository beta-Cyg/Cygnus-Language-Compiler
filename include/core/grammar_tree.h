#ifndef CYG_GRAMMAR_TREE_H
#define CYG_GRAMMAR_TREE_H

#include<map>
#include<fstream>
#include<exception>
#include<initializer_list>

#include"parser.h"

namespace cyg{
	namespace grammar_tree{
		class g_tree_error_code:public std::exception{
		public:
			std::string code_type;

			g_tree_error_code()noexcept{}

			g_tree_error_code(std::string&& c_t):code_type(c_t){}

			const char* what(){
				return code_type.c_str();
			}
		};
		
		class g_tree{
		private:
			cyg::parser::base_struct* root;
			std::string code;
		public:
			explicit g_tree(std::string  _code):root(nullptr),code(std::move(_code)){
				std::string buf("");
				for(auto i:code){
					buf.push_back(i);
					if(i==';'){
						buf.pop_back();
						if(root==nullptr){
							root=new base_struct();
							for(auto i:keywords)
								if(keyword_search(buf,i)){
									//switch()
						//todo push data to the new struct;
								}
						buf.clear();
						continue;
						}
						base_struct* a=new base_struct();
						//todo push data to the new struct
						root->next=a;
						buf.clear();
					}
				}
			}
			
			~g_tree(){
				clear();
			}

			void clear(){
			}
		};

		g_tree parse(std::string file_name){
			std::ifstream fin(file_name);
			std::string file_str="",buf;
			while(getline(fin,buf))file_str+=buf;
			fin.close();
			g_tree gt(file_str);
			return gt;
		}
	}
}

#endif
