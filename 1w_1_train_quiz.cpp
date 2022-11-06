#include <cstdio>
#include <cstdlib>
#include<stdio.h>

typedef struct stationNodeSt {
	struct stationNodeSt *prev;    // 이전 역
	struct stationNodeSt *next;    // 다음 역
	int stationId;	               // 역의 고유 번호
} station;

typedef struct stationListSt {
	station *stations;
	int stationNum;        // 역의 개수
} stationList;

static stationList *g_station_list = NULL;
static int g_station_list_inited = 0;

void initStationList(int constructionNum);
void deinitStationList(void);
station *createStation(int id);
void destroyStation(station *removeStation);
void appendStation(station *newStation);
void removeStation(station *removeStation);
void insertPrevStation(station *currStation, station *newStation);
void insertNextStation(station *currStation, station *newStation);
station *getStationById(int id);
int getTotalStationNum(void);

void BN(int i, int j);
void BP(int i, int j);
void CN(int i);
void CP(int i);

void initStationList(void) {
	if (g_station_list_inited) {
		printf("station list already inited\n");
		return;
	}
	g_station_list = (stationList *)malloc(sizeof(stationList));
	g_station_list->stations = NULL;
}

void deinitStationList(void) {
	for (int i = 0; i < g_station_list->stationNum; i++) {
		station *currStation = getStationById(i);
		if (currStation) {
			removeStation(currStation);
			destroyStation(currStation);
		}
	}
}

station *createStation(int id) {
	station *newStation = (station *)malloc(sizeof(station));

	newStation->prev = NULL;
	newStation->next = NULL;
	newStation->stationId = id;

	return newStation;
}

void destroyStation(station *station) {
	if (station) {
		free(station);
	}
}

void appendStation(station *newStation) {
	if (g_station_list->stations == NULL) {
		g_station_list->stations = newStation;
		g_station_list->stations->prev = g_station_list->stations;
		g_station_list->stations->next = g_station_list->stations;
	} else {
		station *currStation = g_station_list->stations->prev;

		currStation->next->prev = newStation;
		currStation->next = newStation;

		newStation->next = g_station_list->stations;
		newStation->prev = currStation;

	}
	g_station_list->stationNum++;
}

void removeStation(station *removeStation) {
	if (g_station_list->stations == NULL) {
		return;
	}

	if (g_station_list->stations == removeStation) {
		g_station_list->stations = removeStation->next;
		if (g_station_list->stations != NULL) {
			g_station_list->stations->prev = NULL;
		}
		removeStation->prev = NULL;
		removeStation->next = NULL;
	} else {
		station *tempStation = removeStation;
		if (tempStation->prev != NULL) {
			removeStation->prev->next = tempStation->next;
		}
		if (tempStation->next != NULL) {
			removeStation->next->prev = tempStation->prev;
		}
		removeStation->prev = NULL;
		removeStation->next = NULL;
	}
	g_station_list->stationNum--;
}

void insertPrevStation(station *currStation, station *newStation) {
	newStation->prev = currStation->prev;
	if (currStation->prev != NULL) {
		currStation->prev->next = newStation;
	}
	currStation->prev = newStation;
	newStation->next = currStation;
	g_station_list->stationNum++;
}

void insertNextStation(station *currStation, station *newStation) {
	newStation->next = currStation->next;
	if (currStation->next != NULL) {
		currStation->next->prev = newStation;
	}
	currStation->next = newStation;
	newStation->prev = currStation;
	g_station_list->stationNum++;
}

station *getStationById(int id) {
	station *currStation = g_station_list->stations;

	while ((currStation != NULL) && (id > 0))  {
		currStation = currStation->next;
		id--;
	}
	return currStation;
}

station *getStationByStationId(int stationId) {
	station *currStation = g_station_list->stations;
	int count = 0;

	while ((currStation->stationId != stationId) && (count != g_station_list->stationNum)) {
		currStation = currStation->next;
		count++;
	}
	return currStation;
}

/*
    <공사 규칙>
     - 고유 번호 i를 가진 역의 다음 역의 고유 번호를 출력하고, 그 사이에 고유 번호 j인 역을 설립한다.
     - 고유 번호 i를 가진 역의 이전 역의 고유 번호를 출력하고, 그 사이에 고유 번호 j인 역을 설립한다.
     - 고유 번호 i를 가진 역의 다음 역을 폐쇄하고 그 역의 고유 번호를 출력한다.
     - 고유 번호 i를 가진 역의 이전 역을 폐쇄하고 그 역의 고유 번호를 출력한다.

	<입력>
	 - 공사를 시작하기 이전에 있는 역의 개수 : 4
	 - 공사 횟수 : 4
	 - 공사를 시작하기 이전에 있는 역의 고유 번호 : 2 7 3 5 (고유 번호는 서로 달라야 함)

	[공사에 대한 정보]  
	 - BN i j : 고유 번호 i를 가진 역의 다음 역의 고유 번호를 출력하고, 그 사이에 고유 번호 j인 역을 설립한다.
	 - BP i j : 고유 번호 i를 가진 역의 이전 역의 고유 번호를 출력하고, 그 사이에 고유 번호 j인 역을 설립한다.
	 - CN i : 고유 번호 i를 가진 역의 다음 역을 폐쇄하고 그 역의 고유 번호를 출력한다.
	 - CP i : 고유 번호 i를 가진 역의 이전 역을 폐쇄하고 그 역의 고유 번호를 출력한다.

	 [예제 입력]
	 4 4
	 2 7 3 5
	 BN 5 11
	 BP 3 6
	 CP 2
	 CN 7
*/

void BN(int i, int j) {
	int result = 0;
	station *currStation = NULL;
	station *newStation = NULL;

	currStation = getStationByStationId(i);
	result = currStation->next->stationId;

	newStation = createStation(j);
	insertNextStation(currStation, newStation);

	printf("BN %d %d result : %d\n", i, j, result);
}

void BP(int i, int j) {
	int result = 0;
	station *currStation = NULL;
	station *prevStation = NULL;
	station *newStation = NULL;

	currStation = getStationByStationId(i);
	prevStation = currStation->prev;
	result = prevStation->stationId;

	newStation = createStation(j);
	insertPrevStation(currStation, newStation);

	printf("BP %d %d result : %d\n", i, j, result);
}

void CN(int i) {
	int result = 0;
	station *currStation = NULL;
	station *delStation = NULL;

	currStation = getStationByStationId(i);
	delStation = currStation->next;
	result = delStation->stationId;

	removeStation(delStation);
	destroyStation(delStation);

	printf("CN %d result : %d\n", i, result);
}

void CP(int i) {
	int result = 0;
	station *currStation = NULL;
	station *delStation = NULL;

	currStation = getStationByStationId(i);
	delStation = currStation->prev;
	result = delStation->stationId;

	removeStation(delStation);
	destroyStation(delStation);

	printf("CP %d result : %d\n", i, result);
}

int main(void) {
	int constructionNum = 4;
	station *currStation = NULL;

	initStationList();

	currStation = createStation(2);
	appendStation(currStation);
	currStation = createStation(7);
	appendStation(currStation);
	currStation = createStation(3);
	appendStation(currStation);
	currStation = createStation(5);
	appendStation(currStation);

	currStation = g_station_list->stations;

	printf("%d %d\n", g_station_list->stationNum, constructionNum);

	for (int i = 0; i < g_station_list->stationNum; i++) {
		currStation = getStationById(i);
		printf("%d ", currStation->stationId);
	}
	printf("\n");

	BN(5 ,11);
	currStation = getStationById(11);
	BP(3, 6);
	CP(2);
	CN(7);
}