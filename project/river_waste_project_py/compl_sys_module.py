from enum import Enum, auto
import sys
import time  # 참고 : https://dojang.io/mod/page/view.php?id=2463
# import datetime  # 참고 : https://dojang.io/mod/page/view.php?id=2463

# 참고 : https://www.daleseo.com/python-enum/
class err_code(Enum):
	shut_down = auto()  # 1
	ValueErrorInt = auto()  # 2
	ValueErrorChar = auto()  # 3
	UnknownError = auto()  # 4

# 참고 : https://dojang.io/mod/page/view.php?id=2463
def currentDateTime():
	t = time.localtime(time.time())
	return time.strftime('%Y-%m-%d %X', t)

# 참고 : https://www.delftstack.com/ko/howto/python/python-exit-program/
def error(ecode):
	fout.write(ERRORVALUE[ecode.value] + "\n")
	sys.exit(ERRORVALUE[ecode.value])

ROOT = r"project\river_waste_project_py\data"
intxt = ROOT + r"\input.txt"
outtxt = ROOT + r"\output.txt"
ERRORVALUE = {err_code.shut_down: "프로그램 비정상 종료",
				err_code.ValueErrorInt: "ValueErrorInt: int 값이 입력되어야 합니다.",
				err_code.ValueErrorChar: "ValueErrorChar: char 값이 입력되어야 합니다.",
				err_code.UnknownError: "UnknownError: 알 수 없는 오류"}

# 참고 : https://wikidocs.net/26
fin = open(intxt, 'r')
fout = open(outtxt, 'w')

fout.write(f"compl_sys_module.py 실행 시각 {currentDateTime()}\n\n")

if __name__ == "__main__":
	print("excute compl_sys_module.py")
	fin.close()
	fout.close()