var i , j , k : integer ; 
function gcd(i , j : integer ) : integer ; 
begin 
	if i = j then 
		gcd := i ; 
	if i > j then 
		gcd := gcd (i - j , j ) ; 
	if i < j then 
		gcd := gcd (i , j - i ) ; 
end ; 
begin 
	read ( i , j , k ) ; 
	write(gcd(i,j));
	write(" ",gcd(i,gcd(j,k)));
	write(" ",gcd(gcd(i,j),k))
end . 