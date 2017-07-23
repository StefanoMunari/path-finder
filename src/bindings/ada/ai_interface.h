#ifndef AI_INTERFACE_H
#define AI_INTERFACE_H

const int Get_Path_Size(const char * pid_);

const char ** Get_Path(const char * pid_);

void Find(
	const char * pid_,
	const char * source_,
	const char * destination_,
	const int algorithm_);

void Init(
	const char * pid_,
	const char * data_path_,
	const char * f_name_prefix_,
	const char * f_extension_);

void Finalize();

#endif /*AI_INTERFACE_H*/