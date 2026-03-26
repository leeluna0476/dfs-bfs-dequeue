# 사용법
- `make` 필요함.
```bash
make # 기본 옵션으로 빌드.

./solve_maze # 미로 데이터 입력해야 함.
# 또는 data/input 디렉터리에 있는 미로 파일 활용할 수 있음.
./solve_maze < data/input/maze_#x#.txt

make clean # object file 지움.
make fclean # object file 및 실행파일 지움.
make re # make fclean -> make
```
## 변경 가능한 옵션
- 탐색 방향 순서
- 기본 옵션: UP, DOWN, LEFT, RIGHT (왼쪽부터)
```bash
make DIRECTION='"{ UP, DOWN, LEFT, RIGHT }"'
```
  - 중괄호 내부 요소들의 순서 변경하여 탐색 방향 변경 가능함.
  - 입력 양식을 반드시 지켜야 함.

## 기타
- 제어문자를 사용해서 탐색 경로를 magenta 색상으로 표시함. 미로의 입구 및 출구는 cyan 색상으로 표시함.
  - 터미널에 결과를 출력하면 예쁘게 감상할 수 있음.

## 결과 예시
- 20x20 미로. 출구가 있는 경우와 없는 경우를 비교해봄.
- 출구가 없는 미로는 도착 지점이 사방으로 고립되었다는 점 외에는 출구가 있는 미로와 구성이 같음.
![](./images/comparison-sol-nosol-dfs.png)
