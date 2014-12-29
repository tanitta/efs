#pragma once
class Task {
	public:
		unsigned int time_;
		int check_;

		Task(unsigned int time, int check):time_(time), check_(check){};
		virtual ~Task(){};
};
