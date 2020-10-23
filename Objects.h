#ifndef OBJECTS_H
#define OBJECTS_H
#include <list>
#include <iterator> 
#include <iostream>
using namespace std; 

class Vertex
{//This class saves everything related to the vertex of the objects
	private:
		int id;//A variable to identify each vertex in the file
		double x;
		double y;
		double z;
	public:
		Vertex(){}
		Vertex(int id, double x, double y, double z){
			this->id = id;
			this->x = x;
			this->y = y;
			this->z = z;
		}
		int getId(){
			return this->id;
		}
		double getX(){
			return this->x;
		}
		double getY(){
			return this->y;
		}
		double getZ(){
			return this->z;
		}
		void showVertex(){
			cout << "V " << this->x << " " << this->y <<  " " << this->z << endl;
		}
};

class Faces{
	private:
		int id;

	public:	
		list<Vertex> vertices;
		Faces(){}
		Faces(int id){
			this->id = id;
		}

		Faces(int id, list<Vertex> vertices){
			this->id = id;
			this->vertices = vertices;
		}

		int getId(){
			return this->id;
		}

		void addVertex(Vertex v){
			vertices.push_back(v);
		}

		Vertex getVertexID(int id_Vertex){
			Vertex ret;
			list <Vertex> :: iterator it; 
		    for(it = this->vertices.begin(); it != this->vertices.end(); ++it){ 
		        if(it->getId() == id_Vertex){
		        	ret = *it;
		        }
		    }
		    return ret;
		}

		void showVertices(){//Shows the info about each vertex in the face
			list <Vertex> :: iterator it; 
		    for(it = this->vertices.begin(); it != this->vertices.end(); ++it){ 
		        it->showVertex(); 
		    }
		}

		void showFace(){//Shows the vertices of each face but only the ID
			list <Vertex> :: iterator it; 
			cout << "F ";
		    for(it = this->vertices.begin(); it != this->vertices.end(); ++it){ 
		        cout << it->getId() << " "; 
		    }
		    cout << endl; 
		}
};

class Objects{
	private:
		string name;

	public:
		list<Faces> faces;
		Objects(){
		}

		Objects(string name, list<Faces> faces){
			this->name = name;
			this->faces = faces;
		}

		void addFace(Faces f){
			this->faces.push_back(f);
		}

		Faces getFace(int id_Face){
			Faces ret;
			list <Faces> :: iterator it; 
		    for(it = this->faces.begin(); it != this->faces.end(); ++it){ 
		        if(it->getId() == id_Face){
		        	ret = *it;
		        }
		    }
		    return ret;
		}

		void setName(string name){
			this->name = name;
		}

		string getName(){
			return this->name;
		}

		void showAll(list<Vertex> v){//This method shows the info just like it's saved in the obj file
			list <Faces> :: iterator it; 
			list <Vertex> :: iterator it2;
			cout << this->name << " \n";
		    for(it2 = v.begin(); it2 != v.end(); ++it2){ 
		        it2->showVertex();
		    }
		    for(it = this->faces.begin(); it != this->faces.end(); ++it){
		        it->showFace();
		    }
		    cout << endl; 
		}

		void showAll(){//Shows the info saved in each object
			list <Faces> :: iterator it;
			cout << this->name << " \n";
		    for(it = this->faces.begin(); it != this->faces.end(); ++it){
		    	it->showVertices();
		        it->showFace();
		        cout << endl;
		    }
		}
};

#endif