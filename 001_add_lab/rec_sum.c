int rec_sum(int i){

	if(i <= 1){
		return 1;
	}
	else{
		return i + rec_sum(i-1);
	}
}

int main(void){

	int sum = 0;
	sum = rec_sum(sum);

	return 0;
}
