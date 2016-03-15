insertionSort(List, SortedList) :-
  iSort(List, [], SortedList).
iSort([], Accumulator, Accumulator).
iSort([Head | Tail], Accumulator, SortedList) :-
  insert(Head, Accumulator, NewAccumulator),
  iSort(Tail, NewAccumulator, SortedList).
insert(Elem, [Head | Tail], [Head | NewTail]) :-
  Elem @> Head,
  insert(Elem, Tail, NewTail).
insert(Elem, [Head | Tail], [Elem, Head | Tail]) :-
  Elem @=< Head.
insert(Elem, [] , [Elem]).
