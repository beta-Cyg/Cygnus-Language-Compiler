#ifndef CYG_GRAMMAR_TREE_H
#define CYG_GRAMMAR_TREE_H

#include<string>
#include<fstream>
#include<exception>
#include<initializer_list>

namespace cyg{
	namespace grammar_tree{
        std::string keywords[]={"var","import","export","if","for","while","else","elif","proc","return"};

        typedef unsigned long long size_type;

		typedef long double real;

        inline bool is_value(const std::string& name){
            if(name.front()>='0' and name.front()<='9')return false;
            for(auto i:name)
                if(i!='_'){
                    if((i>='a' and i<='z')or(i>='0' and i<='9'))continue;
                    return false;
                }
            return true;
        }

        inline bool is_value(const char& name){
            if(name>='0' and name<='9')return false;
            if(name!='_')
                if(not((name>='a' and name<='z')or(name>='0' and name<='9')))
                    return false;
            return true;
        }

        bool keyword_search(const std::string& code,const std::string& keyword){
            if(code==keyword)return true;
            size_type pos=code.find(keyword);
            if(pos>=code.size())return false;
            if(pos+keyword.size()-1/*the pos of the end of the keyword*/==code.size()-1/*the end of code*/){
                if(is_value(code[pos-1]))return false;
                return true;
            }
            else if(pos==0 and pos+keyword.size()-1<code.size()-1){
                if(is_value(code[pos+keyword.size()]))return false;
                return true;
            }
            else{
                if(is_value(code[pos-1]))return false;
                if(is_value(code[pos+keyword.size()]))return false;
                return true;
            }
            //pos==0 and pos+keyword.size()-1==code.size()-1 : line 34(全匹配)
            //pos==0 and pos+keyword.size()-1<code.size()-1 : 41-44(不达末尾，达开头)
            //pos!=0 and pos+keyword.size()-1==code.size()-1 : line 37-40(达末尾，不达开头)
            //pos!=0 and pos+keyword.size()-1<code.size()-1 : line 45-49(不达末尾，不达开头)
        }

		class type_struct{
		public:
			std::string type_name;
			type_struct(std::string tn="any"):type_name(tn){}
		};

		class base_struct{
		public:
			base_struct* next;
			base_struct(base_struct* _next=nullptr):next(_next){}
		};//base class of the tree node

		class import_struct:public base_struct{
		public:
			std::string module_name;
			base_struct* next;
			import_struct(std::string mn="",base_struct* _next=nullptr):module_name(mn),next(_next){}
		};

		class value_struct:public base_struct{
		public:
			type_struct type_name;
			std::string value_name;
			base_struct* child;
			base_struct* next;
			value_struct(type_struct tn=type_struct(),std::string vn="",base_struct* _child=nullptr,base_struct* _next=nullptr):type_name(tn),value_name(vn),child(_child),next(_next){}
		};

		class expression{
		public:
			std::string exp;

			expression(){}

			expression(std::string&& _exp){
				*this=_exp;
			}

			expression(const char* _exp){
				*this=_exp;
			}

			const expression& operator=(std::string&& _exp){
				exp=_exp;
				return *this;
			}

			const expression& operator=(const std::string& _exp){
				exp=_exp;
				return *this;
			}

			const expression& operator=(const char* _exp){
				exp=_exp;
				return *this;
			}

			std::string parse(){
				return exp;//todo
			}
		};//todo finish the function operate of the class expression

		class if_struct:public base_struct{
		public:
			expression bool_exp;
			base_struct* child;
			base_struct* next;
			if_struct(expression bexp="false",base_struct* _child=nullptr,base_struct* _next=nullptr):bool_exp(bexp),child(_child),next(_next){}
		};

		class for_struct:public base_struct{
		public:
			value_struct for_value;
			expression bool_exp;
			expression change_exp;
			base_struct* child;
			base_struct* next;
			for_struct(value_struct fv=value_struct(),expression bexp="false",expression cexp="",base_struct* _child=nullptr,base_struct* _next=nullptr):for_value(fv),bool_exp(bexp),change_exp(cexp),child(_child),next(_next){}
		};

		class while_struct:public base_struct{
		public:
			expression bool_exp;
			base_struct* child;
			base_struct* next;
			while_struct(expression bexp="false",base_struct* _child=nullptr,base_struct* _next=nullptr):bool_exp(bexp),child(_child),next(_next){}
		};

		class func_struct:public base_struct{
		public:
			value_struct* args;
			type_struct type;
			base_struct* child;
			base_struct* next;
			func_struct(value_struct* _args=nullptr,type_struct tn=type_struct(),base_struct* _child=nullptr,base_struct* _next=nullptr):args(_args),type(tn),child(_child),next(_next){}
		};

		class call_struct:public base_struct{
		public:
			value_struct* args;
			func_struct call_func;
			base_struct* child;
			base_struct* next;
			call_struct(value_struct* _args=nullptr,func_struct cf=func_struct(),base_struct* _child=nullptr,base_struct* _next=nullptr):args(_args),call_func(cf),child(_child),next(_next){}
		};

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
			base_struct* root;
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
                                if(keyword_search(buf,i))
                            //finish it
                            buf.clear();
                            continue;
                        }
                        base_struct* a=new base_struct();
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
