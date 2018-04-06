#include <chrono>
#include <string>
#include <vector>
#include <thread>

#include "fstream"
#include "sstream"
#include "iostream"
#include "ios"

#include "../include/timer.h"
#include "../include/common.h"
#include "../include/mySocket.h"
#include "../include/Decoder.h"
#include "../include/video_reader.h"
#include "../include/data_manager.h"
#include "../include/system_params.h"
#include "../include/path_selector.h"
#include "../include/codeStreaming_parser.h"

#include "../include/myUtility.h"
#include "../include/bitrate_select.h"
#include "../include/fec_param_adjustor.h"


using namespace std;

//two channels' realtime infomation
Channel_Inf chan_inf[NUM_PATH] = {{0.03, 50.0, 50.0}, {0.05, 90.0, 25.0}};
//Tile_Num tile_num{TILE_NUM, FOV_TILE_NUM, 
//	              CUSHION_TILE_NUM, OUTMOST_TILE_NUM};
int tile_num[REGION_NUM] = {FOV_TILE_NUM, CUSHION_TILE_NUM, 
							 OUTMOST_TILE_NUM};
//the unit is Mb/s
double _bitrate[BITRATE_TYPE_NUM] = {50.0, 25.0, 10.0};


int main(int argc, char **argv) {

	Timer t;
	Data_Manager data_manager;

	Video_Reader video_writer;

	vector<Decoder> decoder(NUM_PATH);
	vector<Transmitter> client(NUM_PATH);

	vector<thread> decoder_worker(NUM_PATH);
	vector<thread> writer_worker(NUM_PATH);

	client[0].transmitter_new(argv[1], argv[2], argv[3], argv[4]);
	client[1].transmitter_new(argv[5], argv[6], argv[7], argv[8]);
//	thread setTimer_worker(&Timer::setTimer_td_func, &t, 
//		                   ref(startFlag_one_timeSlice), 
//		                   ref(terminalFlag));	

	for(int i = 0; i < NUM_PATH; i++) {			
		writer_worker[i]  = thread(&Transmitter::receive_td_func, 
			                	   &client[i], i, ref(data_manager));
		decoder_worker[i] = thread(&Decoder::Decoder_td_func,
						 		   &(decoder[i]), i+2, ref(data_manager));
	}
	std::thread writeVideo_worker(&Video_Writer::video_writer_td_func,
								  &video_writer, ref(data_manager));

	//reap or recycle the threads created.	
	writeVideo_worker.join();
	for(int i = 0; i < NUM_PATH; i++) {
//		Decoder_worker[i].join();
		writer_worker[i].join();
	}

//	setTimer_worker.join();
	return 0;

}	