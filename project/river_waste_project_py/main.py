import compl_sys_module as csys

if __name__ == "__main__":
	print("excute main.py")
	csys.fout.write(f"main.py 실행 시각 {csys.currentDateTime()}\n\n")

	csys.fin.close()
	csys.fout.close()