const a0const = 10, c0const = -1, d0const = 'h', e0const = '1';
var a1var, b1var: integer; d1var: array[5] of char;
function calculate(x, y: integer): integer;
begin
    if x >= 1 then
            calculate := calculate(x - 1, y) + y
    else
        calculate := x + y
end;
procedure test(var a1var, b1var:integer);
var loop: integer;
begin
        d1var[2] := 'e';
    d1var[1] := d0const;
        d1var[3] := 'l';
        d1var[4] := d1var[3];
        d1var[0] := 'o';
        write("Letussayhello!");
        for loop := 0 to 4 by 1 do
                write(d1var[loop]);
        write("Doitagaininreverse!");
        for loop := 4 to 0 by -1 do
                write(d1var[loop]);
        write("NowIamgoingtoprintfrom1to10", b1var);
        while(a2var < 10)
        begin
                a1var := calculate(a1var, 1);
                write(",", a1var)
        end;
        write("Anditcomestotheendintheend.");
        write("Insertanywordtoexit!");
        read(a1var)
end;
begin
        write("Pleaseinserttwointegers");
        read(a1var, b1var);
        write("Whatyouinsertare", a1var);
        write("");
        write(b1var);
        if a1var <> 1 then
                a1var := 1;
        if b1var <> 1 then
                b1var := 1;
        test(a1var, b1var)
end.
