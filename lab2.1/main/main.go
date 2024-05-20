package main

import (
	"fmt"
	"go/ast"
	"go/format"
	"go/parser"
	"go/token"
	"os"
)

func changeIntFunctions(file *ast.File, fileset *token.FileSet) {
	ast.Inspect(file, func(node ast.Node) bool {
		funcDecl, ok := node.(*ast.FuncDecl)
		if !ok {
			return true
		}
		if len(funcDecl.Type.Results.List) == 1 { // return only value?
			returnType := funcDecl.Type.Results.List[0].Type

			if ident, ok := returnType.(*ast.Ident); ok && ident.Name == "int" { // return int?
				printFuncName := &ast.ExprStmt{
					X: &ast.CallExpr{
						Fun: &ast.SelectorExpr{
							X:   &ast.Ident{Name: "fmt"},
							Sel: &ast.Ident{Name: "Println"},
						},
						Args: []ast.Expr{&ast.BasicLit{Kind: token.STRING, Value: "\"" + funcDecl.Name.Name + "\""}},
					},
				}

				funcDecl.Body.List = append([]ast.Stmt{printFuncName}, funcDecl.Body.List...)

				// find return statement
				for _, stmt := range funcDecl.Body.List {
					if retStmt, ok := stmt.(*ast.ReturnStmt); ok {
						printReturn := &ast.ExprStmt{ // and print return statement
							X: &ast.CallExpr{
								Fun: &ast.SelectorExpr{
									X:   &ast.Ident{Name: "fmt"},
									Sel: &ast.Ident{Name: "Println"},
								},
								Args: retStmt.Results,
							},
						}

						index := indexOf(funcDecl.Body.List, stmt) // insert before return
						funcDecl.Body.List = append(funcDecl.Body.List[:index], append([]ast.Stmt{printReturn}, funcDecl.Body.List[index:]...)...)
						break
					}
				}
			}
		}

		return true
	})
}

func indexOf(list []ast.Stmt, stmt ast.Stmt) int {
	for i, s := range list {
		if s == stmt {
			return i
		}
	}
	return -1
}

func main() {
	if len(os.Args) != 2 {
		fmt.Printf("usage: astprint <filename.go>\n")
		return
	}

	// Создаём хранилище данных об исходных файлах
	fset := token.NewFileSet()

	// Вызываем парсер
	if file, err := parser.ParseFile(
		fset,                 // данные об исходниках
		os.Args[1],           // имя файла с исходником программы
		nil,                  // пусть парсер сам загрузит исходник
		parser.ParseComments, // приказываем сохранять комментарии
	); err == nil {
		// Если парсер отработал без ошибок, печатаем дерево
		changeIntFunctions(file, fset)
		if format.Node(os.Stdout, fset, file) != nil {
			fmt.Printf("Formatter error: %v\n", err)
		}
		ast.Fprint(os.Stdout, fset, file, nil)
	} else {
		// в противном случае, выводим сообщение об ошибке
		fmt.Printf("Error: %v", err)
	}
}
