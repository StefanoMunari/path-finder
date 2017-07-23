with ai_interface_h;

with Ada.Unchecked_Deallocation;

with Interfaces.C.Strings;
with System.Address_to_Access_Conversions;
with System.Address_Image;

package body AI_Adapter is

	package AI renames ai_interface_h;
	package C_Strings renames Interfaces.C.Strings;

	procedure Init (This : in AI_Adapter.Object;
					Data_Path : String;
					File_Prefix : String;
					File_Extension : String)
	is
		C_AI_Id : C_Strings.chars_ptr :=
			C_Strings.New_String (System.Address_Image (This'Address));
		C_Data_Path : C_Strings.chars_ptr :=
			C_Strings.New_String (Data_Path);
		C_File_Prefix : C_Strings.chars_ptr :=
			C_Strings.New_String (File_Prefix);
		C_File_Extension : C_Strings.chars_ptr :=
			C_Strings.New_String (File_Extension);
	begin
		-- Init the AI instance
		AI.Init (C_AI_Id, C_Data_Path, C_File_Prefix, C_File_Extension);
		-- Free Resources
		C_Strings.Free (C_AI_Id);
		C_Strings.Free (C_Data_Path);
		C_Strings.Free (C_File_Prefix);
		C_Strings.Free (C_File_Extension);
	end Init;

	function Find_Path (This : in AI_Adapter.Object;
						Source : String;
						Destination : String;
						Algorithm : Natural)
		return Infra_Id_List.List
	is
		Path_Size : Integer;
		Path : Infra_Id_List.List;
		C_AI_Id : C_Strings.chars_ptr :=
			C_Strings.New_String (System.Address_Image (This'Address));
		C_Source : C_Strings.chars_ptr := C_Strings.New_String (Source);
		C_Destination : C_Strings.chars_ptr :=
			C_Strings.New_String (Destination);
		C_Algorithm : Integer = Integer (Algorithm);
	begin
		-- Find Path
		-- from Source to Destination using the specified Algorithm
		AI.Find (C_AI_Id, C_Source, C_Destination, C_Algorithm);
		-- Free resources
		C_Strings.Free (C_Source);
		C_Strings.Free (C_Destination);
		-- Get the found Path_Size
		Path_Size := Integer (AI.Get_Path_Size (C_AI_Id));
		-- Get the found Path
		declare
			type C_String_Array is
				array (1 .. Path_Size) of C_Strings.chars_ptr;
			type Ref_C_String_Array is access all C_String_Array;
		    procedure Free_C_Array is new
		      Ada.Unchecked_Deallocation (C_String_Array, Ref_C_String_Array);
			package Ref_CString_Conversion is
			  new System.Address_to_Access_Conversions
			  	(Object => C_String_Array);
			C_Path : Ref_C_String_Array;
		begin
			C_Path :=
				Ref_C_String_Array
				(Ref_CString_Conversion.To_Pointer (AI.Get_Path (C_AI_Id)));
			for Index in 1 .. Path_Size loop
				-- append a String ID
				Path.Append (C_Strings.Value (C_Path (Index)));
			end loop;
			for Index in Path_Size .. 1 loop
				C_Strings.Free (C_Path (Index));
			end loop;
			Free_C_Array (C_Path);
		end;
		-- Free resources
		C_Strings.Free (C_AI_Id);
		-- return the found Path
		return Path;
	end Find_Path;

end AI_Adapter;
