change(Price, Paid, [HalfDollar,Quarter,Dime,Nickel,Penny]):-
  member(HalfDollar,[0,1,2]),
  member(Quarter,[0,1]),
  member(Dime,[0,1,2]),
  member(Nickel,[0,1]),
  member(Penny,[0,1,2,3,4]),
  Sum is 50*HalfDollar + 25*Quarter + 10*Dime + 5*Nickel,
  Sum =< Paid-Price,
  Penny is (Paid - Price) - Sum,
  write("HalfDollars: "),write(HalfDollar),
  write("\nQuarters: "),write(Quarter),
  write("\nDimes: "),write(Dime),
  write("\nNickels: "),write(Nickel),
  write("\nPennies: "),write(Penny).
%want to use as many of the largest coins as possible


/*calc_coins(Cents,[HalfDollar,Quarter,Dime,Nickel,Penny]) :-
  HalfDollar #=< 2,
  HalfDollar #=>0,
  Quarter #=< 2,
  Quarter #=> 0,
  Dime #=< 3,
  Dime #=> 0,
  Nickel #=< 2,
  Nickel #=> 0,
  Penny #=< 4,
  Penny #=> 0,
  S is 5*Nickel + 10*Dime + 25*Quarter + 50*HalfDollar,
  S =< Paid-Price,
  P is Cents-S.*/
