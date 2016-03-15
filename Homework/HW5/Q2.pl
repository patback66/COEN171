find_max(List, Max) :-
   select(Max, List, Tail), \+ (member(Element, Tail), Element > Max).
