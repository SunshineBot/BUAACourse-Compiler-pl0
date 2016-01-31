var s:integer;
function sum(i : integer):integer;
begin
    if i > 1 then 
        sum:=i + sum(i-1)
    else
        sum:=i
end;
begin
    s := sum(5);
    write(s)
end.