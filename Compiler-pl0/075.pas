var g : integer ; 
procedure p1();
	procedure p2();
		procedure p3(var tmp : integer ) ; 
			procedure p4(var tmp : integer ) ; 
			var tmp4 : integer ; 
				procedure p5(var tmp : integer ) ; 
				begin 
					tmp := 5 ; 
				end ; 
			begin 
				p5 (tmp4 ) ; 
				tmp := tmp4 ; 
			end ; 
		begin 
			p4 (tmp ) ; 
		end ; 
	begin 
		p3 (g ) ; 
	end ; 
begin 
	p2 (); 
end ; 
begin 
	p1 (); 
	write ( g ) ; 
end.