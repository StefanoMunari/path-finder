with Ada.Containers.Indefinite_Doubly_Linked_Lists;

use Ada.Containers;

package AI_Adapter is

	package Infra_Id_List is
	  new Ada.Containers.Indefinite_Doubly_Linked_Lists
	  		(Element_Type => String,
	    	"=" => "=");

	type Object is tagged null record;
	type Reference is access all AI_Adapter.Object'Class;

	procedure Init (This : in AI_Adapter.Object;
					Data_Path : String;
					File_Prefix : String;
					File_Extension : String);

	function Find_Path (
				This : in AI_Adapter.Object;
				Source : String;
				Destination : String;
				Algorithm : Natural)
		return Infra_Id_List.List;

end AI_Adapter;
