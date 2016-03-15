last([List|Rest], Last) :- last_(Rest, List, Last).
	last_([], Last, Last).
	last_([List|Rest], _, Last) :- last_(Rest, List, Last).
