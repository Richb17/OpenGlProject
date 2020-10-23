#ifndef FILES_H
#define FILES_H
#include "Objects.h"
#include <iostream>
#include <fstream>
#include<bits/stdc++.h>

using namespace std;

class File
{
	private:
        string name;
        ifstream arch; //The file variable to open the file

    public:
        File(){//an empty constructor

        }

        void fileName(string name){//This method get the file name, in a later part it will contain the obj files for the proyect
        	this->name = name;
        }

        bool open(void){
        	bool resp = true;
    		this->arch.open(name,ios::in);//Open the file
    		if(arch.fail()){ //Checks if the file opened correctly
        		resp = false;
        	}
    		return resp;
        }

        //A method to separe the string in substrings
		//The resultant strings save in a vector of strings
		vector<string> split(string str, char delimiter){
		    vector<string> strings;
		    stringstream ss(str); //transform the string ss in stream
		    string token;
		    while(getline(ss, token, delimiter))
		        strings.push_back(token);
		    return strings;
		}	

		//This method reads from the file and save it into the proper objects
        list<Objects> saveInfo(){
        	vector<string> val;//We have this so we can read the file with out spaces
		    string text;//String to copy all the text
		    int idVertices=1, idFaces=1;
		    list<Objects> objects_in_File;
		    list<Vertex> vertices;
		    Vertex *v = new Vertex();
		    Faces *f = new Faces();
		    Objects *obj = new Objects();
		    bool resp = true/*We have this bool so we can be certain that the file is being read*/, object_found = false;//If there is more than one object in a on obj file we have this boolean to serve as flag
		    while(!arch.eof() && resp)//We do the cycle while the file has something in it
		    {
		        getline(arch,text); //Save one line of the text
		        val = split(text,' ');//We use this method to have a vector of every string in the file per line without the blank spaces
		        if(val.size())//If the vector has members
		        {
		        	if(val[0] == "o" && object_found == false){//When we encounter the object name for the first time
		        		obj->setName(val[0] + " " + val[1]);
		        		object_found = true;
		        	}
		        	else if(val[0] == "o" && object_found == true){//When we encounter a second or following object
		        		obj->showAll(vertices);//We show the last object found on the file
		        		objects_in_File.push_back(*obj);
		        		obj = new Objects();//Restart the object structure for a new object
		        		obj->setName(val[1]);
		        		vertices.clear();//We clear the list of vertices so we don't have a large list of vertices
		        	}
		            else if(val[0] == "v"){//everytime we encounter a vertex
		            	v = new Vertex(idVertices, std::stod(val[1]), std::stod(val[2]), std::stod(val[3]));
		                vertices.push_back(*v);//We add the vertex found to the list of vertices in the file
		                idVertices++;//we add to the vertex counter
		            }
		            else if(val[0] == "f")//When we encounter a face
		            {
		                f = new Faces(idFaces);
		                Vertex *temp = new Vertex();
		                list <Vertex> :: iterator it;//We create an iterator and a temporal vertex to search every vertex in the face we are saving
		                int index;
		                for(int i = 1; i < val.size(); i++){
		                	index = std::stoi(val[i])+1;//we save the id of the vertex we are looking for
		    				for(it = vertices.begin(); it != vertices.end() && it->getId() != index; ++it)//we search in the list of all vertices until we found it
		    					*temp = *it;
		                    f->addVertex(*temp);//we add the vertex to the face's list of vertices
		                }
		                obj->addFace(*f);//We add the face to the object's list of faces
		                idFaces++;
		            }
		        }
		    }
		    obj->showAll(vertices);//We show the last object found on the file
		    objects_in_File.push_back(*obj);
		    arch.close();//Close the archive
		    return objects_in_File;
        }

        //Getters
        string getName(void){
        	return this->name;
        }  
};

#endif // FILE_H