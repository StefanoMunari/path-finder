#ifndef AI_INTERFACE_H
#define AI_INTERFACE_H

int Get_Path_Size(char * type_id_, char * agent_id_);

char ** Get_Path(char * type_id_, char * agent_id_);

bool Find(
   char * type_id_,
   char * agent_id_,
   char * source_,
   char * destination_,
   int algorithm_);

bool Set_Clients_Limit(int clients_limit);

bool Init(
   char * type_id_,
   char * agent_id_,
   char * data_path_,
   char * f_name_prefix_,
   char * f_extension_);

bool Finalize();

#endif /*AI_INTERFACE_H*/