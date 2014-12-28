#pragma once
#include <Issue.h>

class Grid : public ofxTUIBaseWindow{
	Issue issue_ref_;
	public:
		Grid(Issue& i):ofxTUIBaseWindow(50,50,0,0),issue_ref_(i){};
		virtual ~Grid(){};
		virtual void draw(){

		};
};
