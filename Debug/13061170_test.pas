const pi = 3;
var i,j,k:integer;
        num:integer;
    ch:char;
    numarr: array[4] of integer;
procedure procA();
    var a:integer;
    procedure procB();
        var b:integer;
        procedure procC();
            var c:integer;
            procedure procD();
                var d:integer;
            begin
                a := 27;
                write("procD : ",a)
            end;
        begin
            write("procC : ",a);
            procD()
        end;
    begin
        write("procB : ",a);
        procC()
    end;
begin
    a:=1;
    write("procA : ",a);
    procB()
end;
procedure helloworld();
begin
    write("hello, pascal!")
end;
procedure addition(k,l:integer; var r:integer);
var s:integer;
begin
    s := k + l;
    r := s
end;
function allAddition(k,l:integer):integer;
var s,t:integer;
begin
    if k>=l then
    begin
        t := k;
        k := l;
        l := t
    end;
    s := 0;
    for t := k to l by 1 do
        s := s + t;
    allAddition := s
end;
function getFive():integer;
var n:integer;
begin
        getFive := 5
end;
function getI():integer;
begin
    getI := i
end;
begin
        i:=3;
        write(i);
        write("allAddition : ", allAddition(3,5));
        addition(3,7,k);
        write("addition of 3 and 7 : ", k);
        helloworld();
        write("please type in a number : ");
        read(num);
        write("you have typed in : ",num);
        write(", and this is a five: ", getFive());
        write(". now initialize an array:");
        for i := 0 to 4 by 1 do
        begin
                numarr[i] := -i;
                write("numarr[",i);
                write("] = ",i);
                write(", ")
        end;
        write("i^3 :");
        while i >= 0 do
        begin
                write(" ",i * i * i);
                i := i - 1    
        end;
        write(", allAddition of 10 and 5 :", k);
        write(". PI = ",pi);
        write(". getI = ", getI());
        procA()
end.