% Лабораторная работа № 1.1. Раскрутка самоприменимого компилятора
% 6 марта 2024 г.
% Егор Поршенко, ИУ9-61Б

# Цель работы
Целью данной работы является ознакомление с раскруткой самоприменимых компиляторов 
на примере модельного компилятора.

# Индивидуальный вариант
Компилятор P5. Сделать идентификаторы и ключевые слова чувствительными к регистру.


# Реализация

Различие между файлами `pcom.pas` и `pcom2.pas`:

```diff
@@ -827,7 +827,7 @@
   var m: boolean; i: integer;
   begin
     m := true;
-    for i := 1 to reslen do if lcase(a[i]) <> lcase(b[i]) then m := false;
+    for i := 1 to reslen do if a[i] <> b[i] then m := false;
     for i := reslen+1 to maxids do if b[i] <> ' ' then m := false;
     strequri := m
   end { equstr };
@@ -953,8 +953,8 @@
     while (a <> nil) or (b <> nil) do begin
       i := 1;
       while (i <= varsqt) and ((a <> nil) or (b <> nil)) do begin
-        if a <> nil then ca := lcase(a^.str[i]) else ca := ' ';
-        if b <> nil then cb := lcase(b^.str[i]) else cb := ' ';
+        if a <> nil then ca := a^.str[i] else ca := ' ';
+        if b <> nil then cb := b^.str[i] else cb := ' ';
         if ca <> cb then begin a := nil; b := nil end;
         i := i+1
       end;
@@ -970,7 +970,7 @@
     m := true; j := 1;
     for i := 1 to maxids do begin
       c := ' '; if a <> nil then begin c := a^.str[j]; j := j+1 end;
-      if lcase(c) <> lcase(b[i]) then m := false;
+      if c <> b[i] then m := false;
       if j > varsqt then begin a := a^.next; j := 1 end
     end;
     strequvf := m
@@ -983,10 +983,10 @@
     m := true; i := 1; j := 1;
     while i < maxids do begin
       c := ' '; if a <> nil then begin c := a^.str[j]; j := j+1 end;
-      if lcase(c) <> lcase(b[i]) then begin f := i; i := maxids end else i := i+1;
+      if c <> b[i] then begin f := i; i := maxids end else i := i+1;
       if j > varsqt then begin a := a^.next; j := 1 end
     end;
-    strltnvf := lcase(c) < lcase(b[f])
+    strltnvf := c < b[f]
   end;

```

Различие между файлами `pcom2.pas` и `pcom3.pas`:

```diff
@@ -1378,7 +1378,7 @@
                     until chartp[ch] <>  number
                 end;
               if lcase(ch) = 'e' then
-                begin k := k+1; if k <= DIGMAX then digit[k] := ch;
+                begin k := k+1; if k <= digmax then digit[k] := ch;
                   nextch;
                   if (ch = '+') or (ch ='-') then
                     begin k := k+1; if k <= digmax then digit[k] := ch;
@@ -1481,7 +1481,7 @@
              until iscmte or (ch = ')') or eof(input);
              if not iscmte then nextch; goto 1
            end
-         else if ch = '.' then begin sy := LbRaCk; nextch end
+         else if ch = '.' then begin sy := lbrack; nextch end
          else sy := lparent; 
          op := noop
        end;

```

# Тестирование

Тестовый пример:

```pascal
program hello(output);
var
    a, b, result : integer;

begin
    a := 1;
    b := 2;
    result := a + b;
    writeln(RESULT);
    writeln('Hello, world');
END.

```

Вывод тестового примера на `stdout`

```
P5 Pascal interpreter vs. 1.0

Assembling/loading program
Running program

P5 Pascal compiler vs. 1.0


     1       40 program hello(output); 
     2       40 var 
     3       40     a, b, result : integer; 
     4       52  
     5       52 begin 
     6        3     a := 1; 
     7        7     b := 2; 
     8        9     result := a + b; 
     9       13     writeln(RESULT); 
     9   ****                    ^104
    10       16     writeln('Hello, world'); 
    11       24 END. 
    11   ****     ^104
   *** eof encountered

    12   ****  ,2,6,51,6,13,6,21

Errors in program: 9

Error numbers in listing:
-------------------------
  2  Identifier expected
  6  Illegal symbol
 13  'end' expected
 21  '*' expected
 51  ':=' expected
104  Identifier not declared

```
Результат: идентификаторы и ключевые слова действительно стали чувствительны к регистру 
(ключевые слова теперь определены только в нижнем регистре).
# Вывод
В результате выполнения лабораторной работы ознакомился с концепцией самоприменимых компиляторов 
на примере компилятора P5 языка Pascal. Выполнение задачи было сложным, поскольку было тяжело 
ориентироваться в исходном коде компилятора (отсутствие комментариев, зачастую непонятный нейминг, 
также в принципе большой объём кода). Однако с момента нахождения точки, 
которая отвечает за преобразование строк, и, соответственно, чувствительность к регистру,
задача решилась быстро.