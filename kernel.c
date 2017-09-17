void dummy_test_entrypoint() {
}

void main() {
	int i = 0;
	char* video_memory = (char*) 0xb8000;
	*video_memory = 'Z';
	for(i = 0; i < 10; ++i) {
		video_memory++;
		*video_memory = 'A';
	}
}