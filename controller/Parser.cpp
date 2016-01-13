#include "Parser.h"

String GetArgument(String line, byte arg){
	String intersection = StringIntersection(line, '[', ']');

	if(intersection != ""){
		byte argumentCount = 0;

		for(byte i = 0; i < intersection.length(); i++){
			if(intersection.charAt(i) == ';'){
				argumentCount ++;
			}
		}

		if(arg <= argumentCount){
			String split = StringSplit(intersection, ';', arg);
			
			if(split != ""){
				return split;
			}
		}
	}	
    
	return "";
}

byte GetPacketId(String line){
	String id = GetArgument(line, 0);

	if(id == ""){
		return 0;
	}

	return id.toInt();
}

