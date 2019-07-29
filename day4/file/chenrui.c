#include<stdio.h>
   #include<stdlib.h>
   #include<sys/types.h>
   #include<dirent.h>
   #include<string.h>
   int print(char*argv,int width){
	          struct dirent* dir;                                            
			         DIR*p;
					       char buf[1024]={0};
						         p=opendir(argv);//打开一个目录
								       while((dir=readdir(p))){//将目录读取完
										             if(!strcmp(dir->d_name ,".")||!strcmp(dir->d_name ,"..")){
														                       continue;
																			             }
													           printf("%*s%s\n",width,"",dir->d_name );
															             sprintf(buf  ,"%s%s%s",argv ,"/",dir->d_name );
																		           if(dir->d_type==4){//如果类型为目录类型
																					                  print(buf  ,width+4);
																									            }
																				     
																				         }
									         closedir(p);
											       return 0;
												     }
  
  int main(int argc,char*argv[]){
	        print(argv[1],4);
			      return 0;
				    
				    }
