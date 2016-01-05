const min=7,max=30;
var product,index,num,temp:integer;
	prime:array[10]of integer;
	
procedure error( n : integer ); 
begin
   	if n = 1 then
   		write("range should more than 6")
   	else
   		write("range should less than 31")
end;

function maxdivisor (a,b:integer):integer;
var result,subtractor,minued:integer;
begin
	if a>b
	then
		begin
			subtractor:=b;
			result:=a-b
		end
	else
		begin 
			subtractor:=a; 
			result:=b-a
		end;
	if result=0
	then
		maxdivisor:=a
	else
		maxdivisor:=maxdivisor(result,subtractor)
end;

procedure getprime();
var i,j,flag,returnvalue:integer;
begin
	for i:=7 to num by 1 do 
	begin
		flag:=1;
		for j:=2 to 6 by 1 do
		begin
			returnvalue:=maxdivisor(i,j);
			if returnvalue>1
			then flag:=0
		end ;
		if flag=1 
		then
		begin
			prime[index]:=i;
			index:=index+1
		end
	end
end;

begin
	write("input max number");
	read(num);
	if num>max
		then error(1)
	else
		if num<min
		then error(0)
		else begin
			index:=0;
			getprime();
			index:=index-1;
			product:=1;
			for num:=0 to index by 1 do
			begin
				temp:=prime[num];
				product:=product*prime[num];
				write(temp)
			end;
			write(product)
			end
end.
		
