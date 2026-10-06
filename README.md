# PocketInventory

**상품과 재고, 입출고 이력을 한곳에서 관리하는 데스크톱 앱**

PocketInventory는 C++와 Qt Quick으로 만든 재고 관리 프로그램입니다. 상품별 수량과 최소 재고, 단가, 카테고리를 관리하고 대시보드에서 재고 현황을 확인할 수 있습니다. 데이터는 로컬 SQLite 파일에 저장됩니다.

[Windows 배포 버전 다운로드](https://github.com/ldh940627/PocketInventory/releases/latest) · [변경 사항 및 릴리스](https://github.com/ldh940627/PocketInventory/releases) · [문제 제보](https://github.com/ldh940627/PocketInventory/issues)

## 빠른 시작

1. [릴리스 페이지](https://github.com/ldh940627/PocketInventory/releases/latest)의 **Assets**에서 `PocketInventory-0.1-Windows-x64.zip`을 다운로드합니다.
2. 쓰기 가능한 폴더에 ZIP 전체를 압축 해제합니다.
3. `appPocketInventory.exe`를 실행합니다.

현재 배포 파일은 **Windows 64비트용**입니다. Qt 라이브러리와 컴파일러 런타임이 포함되어 있어 Qt를 따로 설치할 필요가 없습니다. 실행 파일과 함께 제공되는 DLL 및 하위 폴더를 그대로 유지하세요.

> 실행용 파일은 `PocketInventory-0.1-Windows-x64.zip`입니다. GitHub가 제공하는 `Source code` 압축 파일은 개발용 소스입니다.

## 주요 기능

| 화면 | 기능 |
| --- | --- |
| 대시보드 | 전체 상품 수, 정상·부족 재고 수, 총 재고 금액, 부족 재고 목록, 최근 변경 이력, 카테고리별 요약 |
| 재고 관리 | 상품 등록·수정·삭제, 입고·출고, 수량 증감, 상품명 검색, 재고 상태 및 카테고리 필터 |
| 변경 이력 | 상품별 변경 기록 조회, 상품명·변경 유형·기간 필터, 최신순·오래된순 정렬 |
| CSV | 전체 상품 목록 내보내기, CSV 파일에서 상품 일괄 등록 |

상품에는 상품명, 현재 재고, 최소 재고, 단가, 카테고리를 저장합니다. **현재 재고가 최소 재고 이하이면 부족 재고**로 표시하며, 재고 금액은 현재 재고 × 단가로 계산합니다.

## 사용 흐름

1. **재고 관리**에서 상품명, 초기 수량, 최소 재고, 단가와 카테고리를 입력해 상품을 등록합니다.
2. 입고·출고 기능으로 수량을 변경합니다.
3. **대시보드**에서 부족한 상품과 전체 재고 금액을 확인합니다.
4. **변경 이력**에서 등록, 입출고, 수량 변경, 수정·삭제 기록을 조회합니다.
5. 상품 목록을 CSV로 내보내거나, 정해진 형식의 CSV로 새 상품을 일괄 등록합니다.

## CSV 형식

CSV는 UTF-8로 저장하며, 첫 줄의 열 이름과 순서는 아래 형식과 일치해야 합니다.

```csv
상품명,카테고리,현재재고,최소재고,단가,재고금액
볼펜,문구,30,10,1000,30000
노트,문구,5,10,2500,12500
```

- 현재 재고, 최소 재고, 단가는 0 이상의 정수입니다.
- 카테고리를 비워 두거나 `미분류`로 입력하면 미분류 상품으로 등록됩니다.
- 같은 CSV 안에 중복 상품명이 있거나 이미 등록된 상품명이 포함되면 가져오기가 거부됩니다.
- 가져오기는 **새 상품 등록** 기능입니다. 기존 상품을 덮어쓰지 않습니다.
- `재고금액` 열은 형식상 필요하지만 가져올 때 값을 사용하지 않으며, 앱에서 수량과 단가로 계산합니다.
- 내보내기는 현재 검색·필터 결과와 관계없이 **전체 상품**을 대상으로 합니다.

CSV는 상품 데이터 교환용입니다. 변경 이력까지 보관하려면 아래의 데이터 폴더를 백업하세요.

## 데이터 저장 및 백업

첫 실행 시 실행 파일 옆에 데이터 폴더와 SQLite 데이터베이스가 생성됩니다.

```text
PocketInventory-0.1-Windows-x64/
├── appPocketInventory.exe
├── data/
│   └── pocket_inventory.db
├── qml/
├── platforms/
└── ... Qt 라이브러리 및 플러그인
```

**앱을 종료한 뒤 `data` 폴더 전체를 복사**하면 상품과 변경 이력을 백업할 수 있습니다. 새 버전으로 옮길 때도 앱을 종료하고 기존 `data` 폴더를 새 실행 파일 옆으로 복사하세요.

배포 ZIP에는 기존 재고 데이터가 포함되어 있지 않습니다. 데이터가 실행 폴더에 저장되므로 `Program Files`처럼 쓰기 권한이 제한된 위치는 피하세요.

## 기술 구성

| 구분 | 사용 기술 |
| --- | --- |
| 애플리케이션 로직 | C++ |
| 사용자 인터페이스 | QML, Qt Quick, Qt Quick Controls 2 |
| 데이터 저장 | SQLite, Qt SQL |
| 빌드 | CMake |
| 배포 확인 환경 | Qt 6.11.1 / MinGW 64-bit / Windows |

QML 화면과 C++ ViewModel을 연결하고, Service에서 재고 변경과 트랜잭션을 처리하며, Repository에서 SQL을 실행하는 구조입니다.

```text
QML 화면 → ViewModel / Model → Service / Repository → SQLite
```

## 소스에서 빌드

### 준비 사항

- Qt 6.10 이상 — 배포 빌드는 Qt 6.11.1 사용
- Qt Quick, Qt Quick Controls 2, Qt SQL 모듈
- Qt 설치 버전과 호환되는 C++ 컴파일러
- CMake 3.16 이상
- Qt Creator 권장

### Qt Creator

1. 저장소를 복제합니다.

   ```sh
   git clone https://github.com/ldh940627/PocketInventory.git
   ```

2. Qt Creator에서 `CMakeLists.txt`를 엽니다.
3. Qt 6 Desktop Kit를 선택합니다.
4. 빌드 구성을 `Release`로 선택하고 빌드·실행합니다.

> v0.1.0 소스에는 `productfilterproxymodel.h`의 `categoryFilter` 속성에 `WRITE setCategoryFIlter` 오타가 있습니다. 해당 코드가 남아 있다면 `WRITE setCategoryFilter`로 수정한 뒤 빌드하세요. 배포 ZIP에는 이 수정이 반영되어 있습니다.

### Windows 명령줄 예시

Qt 및 MinGW 도구가 PATH에 설정된 터미널에서 실행합니다. Qt 설치 경로는 환경에 맞게 바꾸세요.

```powershell
cmake -S . -B build/release -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="C:/Qt/6.11.1/mingw_64"
cmake --build build/release --parallel
./build/release/appPocketInventory.exe
```

## 프로젝트 구조

```text
PocketInventory/
├── CMakeLists.txt                # Qt 모듈 및 빌드 설정
├── main.cpp                     # 객체 구성 및 QML 엔진 초기화
├── Main.qml                     # 앱의 기본 창과 화면 전환
├── Pages/                       # 대시보드, 재고 관리, 변경 이력
├── components/                  # 공통 UI, 테이블, 다이얼로그, 테마
├── inventoryviewmodel.*          # 재고 화면과 C++ 로직 연결
├── inventoryservice.*            # 재고 작업 및 트랜잭션
├── productmodel.*                # 상품 목록 모델
├── productfilterproxymodel.*     # 상품 검색 및 필터
├── productrepository.*          # 상품 데이터 접근
├── history*.cpp / history*.h     # 이력 모델, 필터, ViewModel, Repository
├── DatabaseManager.cpp          # DB 연결, 테이블 생성 및 마이그레이션
├── databasemanager.h
└── service/csvservice.*          # CSV 읽기 및 쓰기
```

## 문제 제보

오류나 개선 의견은 [Issues](https://github.com/ldh940627/PocketInventory/issues)에 남겨 주세요. 사용 중인 버전, 재현 순서, 기대한 동작과 실제 동작을 함께 적으면 확인에 도움이 됩니다.

