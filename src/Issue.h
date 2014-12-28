#pragma once
class Issue {
	private:
		std::string index_;
		int level_;
		vector<int> tasks_;
	public:
		Issue():index_(""),level_(1),tasks_(){};
		virtual ~Issue(){};
};

