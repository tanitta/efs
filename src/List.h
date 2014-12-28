#pragma once
class List : public ofxTUIBaseWindow{
	private:
	Issue issue_ref_;
	public:
		List(Issue& i):ofxTUIBaseWindow(50,50,0,0),issue_ref_(i){};
		virtual ~List(){};
};
