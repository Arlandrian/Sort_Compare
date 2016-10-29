#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void bubble(int *arr,int N );
void selection(int *arr,int N);
void swap(int *a,int *b);
void merge(int *arr, int low, int mid, int high);
void arr_print(int *arr,int N);
void mergesort(int *arr, int low, int high);
int main(int argc, char *argv[]) {

	//N alinan sayi,ijk for donguler icin degiskenler,toplam ortalama hesaplamasi icin kullanilan dizi
	int N,j,i,k,kac_kere;//kac_kere=>sortlari kac kere yapilacagini tutan degisken
	
	int *temp_dizi,*sabit_dizi;
	//ortalamalari bulmak icin toplam süreleri tutacagimiz degiskenler
	float selection_t=0,bubble_t=0,merge_t=0;
	//basla bitir fonksiyonlardan once ve sonra zamani alip 
	float basla,bitir,T;
	char shutdown;
	system("COLOR 02");
	printf("Program durduktan sonra bilgisayarin kapanmasini istermisiniz?(Y/N):");
	scanf("%c",&shutdown);
	printf("\nN sayisini girin: \n");
	scanf("%d",&N);
	srand(time(NULL));
	//dizi siralandiktan sonra ayni diziyi baska 3 algoritmayla da siralamamiz icin eski diziyi 2. bir dizide tutmamiz gerekiyor(sabit dizi)...
	sabit_dizi = (int *) malloc(sizeof(int)*N);
	if(!sabit_dizi){
		printf("Bellekte yeterli yer yok.");
	}
	temp_dizi = (int *) malloc(sizeof(int)*N);
	if(!temp_dizi){
		printf("Bellekte yeterli yer yok.");
	}

	printf("\n");
	printf("Kac farkli sort suresi olcmek istersiniz?\n");
	scanf("%d",&kac_kere);

	printf("   Merge Sort     Selection Sort      Bubble Sort\n");
	printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
	for(k=0;k<kac_kere;k++){	
		//dizi atamasi
		for(i=0;i<N;i++){
			*(temp_dizi+i) = rand();
			*(sabit_dizi+i)= *(temp_dizi+i);
		//	printf("%d ",*(temp_dizi+i));//karisik diziyi gormek icin...
		}
		//Merge_Sort
		
		basla=clock();
		mergesort(temp_dizi,0,N);
		bitir=clock();
		T=(bitir-basla)/1000;
		printf("%d-)%.3f sn",k+1,T);
		//Merge sort icin toplam sure
		merge_t=merge_t+T;				

		//sirali diziyi yazdirmak icin
		/*
		printf("\nMerge sirali dizi:\n");
		arr_print(temp_dizi,N);
		getch();
		*/
		
		//ayni diziyi siralamak icin sabit diziyi  yeniden temp e atiyoruz
		for(i=0;i<N;i++){
			*(temp_dizi+i) = *(sabit_dizi+i);
		}
		
		//selection
		basla=clock();
		selection(temp_dizi,N);
		bitir=clock();
		T=(bitir-basla)/1000;
		//sirali diziyi yazdirmak icin
		/*
		printf("\nSelection sirali dizi:\n");
		arr_print(temp_dizi,N);
		getch();
		*/
		printf("         %.3f sn",T);
		//selection sort icin toplam sure
		selection_t=selection_t+T;	
		for(i=0;i<N;i++){
			*(temp_dizi+i) = *(sabit_dizi+i);
		}
		
		//Bubble
		basla=clock();
		bubble(temp_dizi,N);
		bitir=clock();
		T=(bitir-basla)/1000;
		//sirali diziyi yazdirmak icin
		/*
		printf("\nBubble sirali dizi:\n");
		arr_print(temp_dizi,N);
		getch();
		*/
	
		printf("           %.3f sn\n",T);
		//Bubble Sort icin toplam sure
		bubble_t=bubble_t+T;
	}

	printf("Siralamar Tamamlandi.\n%d sayi iceren dizi icin\n",N);
	printf("Merge Sort Ortalama %.3f surdu.\n",merge_t/kac_kere);
	printf("Selection Sort Ortalama %.3f surdu.\n",selection_t/kac_kere);
	printf("Bubble Sort Ortalama %.3f surdu.\n",bubble_t/kac_kere);
	
	system("C:\\users\\alo_i\\Desktop\\Screenshot.bat /s");
	
	free(temp_dizi);
	free(sabit_dizi);
	printf("\n%c",shutdown);
	if( shutdown == 'Y' || shutdown== 'y' ){
		printf("Bilgisay Kapaniyor...");
		system("C:\\WINDOWS\\System32\\shutdown.exe /s");
	}
		
	return 0;
}

void bubble(int *arr,int N ){
 	int i,j,temp;
	for(i=1;i<N;i++){
		
		for(j=0;j<N-i;j++){
			
			if(*(arr+j)>*(arr+j+1)){
				swap((arr+j),(arr+j+1));
			}
		}
		//Ne  kadar ilerledigini gormemiz icin(runtime i cok fazla uzatiyor!)
		/*
		system("cls");
		printf("yuzde:%d\n",100*i/N);
		*/
	}
}

void selection(int *arr,int N){
 
  int i,j;

	for (j = 0; j < N-1; j++) 
  		{
    	int iMin = j;
    
    	for ( i = j+1; i < N; i++) {
        
        	if (*(arr+i) < *(arr+iMin)) {
            
            iMin = i;
        	}
    	}

    	if(iMin != j) 
    	{
        	swap((arr+j), (arr+iMin));
    	}
	}
}

void mergesort(int *arr, int low, int high){
    if (low < high) {
        int m = (high + low)/2;
        mergesort(arr, low, m);
        mergesort(arr, m + 1, high);
        merge(arr, low, m, high);
    }
}

void merge(int *arr, int low, int mid, int high){
	
	int *arr2;
    
    arr2=(int *)malloc(sizeof(int)*(high-low+1));
    int i = low, j = mid+1, k = 0;
  
    while (i <= mid && j <= high) {
        if (*(arr+i) <= *(arr+j))
            *(arr2+k++) = *(arr+i++);
        else
            *(arr2+k++) = *(arr+j++);
    }
    while (i <= mid)
        *(arr2+k++) = *(arr+i++);
  
    while (j <= high)
       *(arr2+k++)  = *(arr+j++);
  
    k--;
    while (k >= 0) {
        *(arr+low + k)= *(arr2+k);
        k--;
    }
    free(arr2);
}

void arr_print(int *arr,int N){
	int i;
	for(i=0;i<N;i++){
		printf("%d ",*(arr+i));
	}
}

void swap(int* a,int* b){
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}
