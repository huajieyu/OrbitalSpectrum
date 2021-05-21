void readprocess_em(){
	std::vector<string> orbital;
	orbital.push_back("1d32");
	orbital.push_back("2s12");
	orbital.push_back("1d52");
	orbital.push_back("1p12");
	orbital.push_back("1p32");
	orbital.push_back("1s12");
	orbital.push_back("1f72");

	const static int ROW=orbital.size();

	std::vector<string> COL[ROW];


   for(int ir=0; ir<ROW; ir++){
      COL[ir].clear();
      if(ir==0){ //1d32
           COL[ir].push_back("1.0");
           COL[ir].push_back("1.5");
           COL[ir].push_back("2.0");
      } else if(ir==1){ //2s12
           COL[ir].push_back("1.0");
           COL[ir].push_back("1.5");
           COL[ir].push_back("2.0");
 
      } else if(ir==2){ //1d52
           COL[ir].push_back("2.0");
           COL[ir].push_back("3.0");
           COL[ir].push_back("4.0");
           COL[ir].push_back("5.0");
           COL[ir].push_back("6.0");
      } else if(ir==3){  //1p12
           COL[ir].push_back("4.0");
           COL[ir].push_back("5.0");
           COL[ir].push_back("6.0");
           COL[ir].push_back("7.0");
           COL[ir].push_back("8.0");
           COL[ir].push_back("9.0");
           COL[ir].push_back("10.0");
      } else if(ir==4){  //1p32
           COL[ir].push_back("4.0");
           COL[ir].push_back("5.0");
           COL[ir].push_back("6.0");
           COL[ir].push_back("7.0");
           COL[ir].push_back("8.0");
           COL[ir].push_back("9.0");
           COL[ir].push_back("10.0");
      } else if(ir==5){  //1s12
           COL[ir].push_back("10.0");
           COL[ir].push_back("12.0");
           COL[ir].push_back("14.0");
           COL[ir].push_back("16.0");
           COL[ir].push_back("18.0");
           COL[ir].push_back("20.0");
           COL[ir].push_back("22.0");
           COL[ir].push_back("24.0");
           COL[ir].push_back("26.0");
           COL[ir].push_back("28.0");
           COL[ir].push_back("30.0");   
      }
      else if(ir==6){ //1f72
           COL[ir].push_back("1.0");
           COL[ir].push_back("1.5");
           COL[ir].push_back("2.0");
      }
	//else if(ir==7){
        //   COL[ir].push_back("corr");
        //}

   }



  TFile *outputROOTFile = new TFile("OUTPUT_ANALYSIS.root", "RECREATE");


  //open a txt file and 
  for(int iorb=0; iorb<orbital.size();iorb++){
     if(iorb>0) break; 
     for(int iw=0; iw<COL[iorb].size(); iw++){
	  if(iw>0) break;
	  //if(isyst > 6) continue;
	  std::cout<<"iorb = "<<iorb<<std::endl;
	  std::string inputfilestring;
	  inputfilestring = "/dune/data/users/jiangl/sf_Ti48_DHB_"+orbital[iorb]+"_"+COL[iorb][iw]+".txt";

	  //std::cout<<inputfilestring<<std::endl;

	  //open the while and readin line by line
	  ifstream stat_file_Em;
	  stat_file_Em.open(inputfilestring.c_str());
	  string line_stat_Em;

	  std::vector<double> spec_Em_bin[200];
	  std::vector<double> spec_Em_amp[200];
	  std::vector<double> test_Em;
	  for(int i=0; i<200;i++){
		spec_Em_bin[i].clear();
		spec_Em_amp[i].clear();

	  }
	  double temp_Pm[200];
	  int index=0;
	  while(!stat_file_Em.eof()){
	          getline(stat_file_Em, line_stat_Em);
		  int binnum=index/801;

		  //if(index>800) break;
		  if(index%801==0){
			stringstream ssPm(line_stat_Em);
			double tempPm=0;
			while(ssPm>>tempPm){
				temp_Pm[index%800]=tempPm;
			}		
		  } 
		  else{ 
		  string tmp_Em_num1="";
		  string tmp_Em_num2="";
		  string tmp_Em_num3="";
		  string tmp_Em_num4="";
		  string tmp_Em_num5="";

		  string tmp_spec_num1="";
		  string tmp_spec_num2="";
		  string tmp_spec_num3="";
		  string tmp_spec_num4="";
		  string tmp_spec_num5="";

	          stringstream ss_Em(line_stat_Em);
	          while(ss_Em >> tmp_Em_num1>>tmp_spec_num1>>tmp_Em_num2>>tmp_spec_num2>>
				 tmp_Em_num3>>tmp_spec_num3>>tmp_Em_num4>>tmp_spec_num4>>
				 tmp_Em_num5>>tmp_spec_num5){

			//std::cout<<tmp_Em_num1<<"   "<<tmp_spec_num1<<"  "<<tmp_Em_num2<<"   "<<tmp_spec_num2<<"  "<<tmp_Em_num3<<"   "<<tmp_spec_num3<<"  "<<tmp_Em_num4<<"   "<<tmp_spec_num4<<"  "<<tmp_Em_num5<<"   "<<tmp_spec_num5<<std::endl;
	                spec_Em_bin[binnum].push_back(std::stod(tmp_Em_num1));
	                spec_Em_bin[binnum].push_back(std::stod(tmp_Em_num2));
	                spec_Em_bin[binnum].push_back(std::stod(tmp_Em_num3));
	                spec_Em_bin[binnum].push_back(std::stod(tmp_Em_num4));
	                spec_Em_bin[binnum].push_back(std::stod(tmp_Em_num5));
			
			//std::cout<<std::stold(tmp_spec_num1)<<std::endl;
				
			//std::cout<<std::stod(tmp_spec_num1)/(4*TMath::Pi()*temp_Pm[binnum]*temp_Pm[binnum])<<std::endl;
	                spec_Em_amp[binnum].push_back(std::stold(tmp_spec_num1)/(4*TMath::Pi()*temp_Pm[binnum]*temp_Pm[binnum]));
	                spec_Em_amp[binnum].push_back(std::stold(tmp_spec_num2)/(4*TMath::Pi()*temp_Pm[binnum]*temp_Pm[binnum]));
	                spec_Em_amp[binnum].push_back(std::stold(tmp_spec_num3)/(4*TMath::Pi()*temp_Pm[binnum]*temp_Pm[binnum]));
	                spec_Em_amp[binnum].push_back(std::stold(tmp_spec_num4)/(4*TMath::Pi()*temp_Pm[binnum]*temp_Pm[binnum]));
	                spec_Em_amp[binnum].push_back(std::stold(tmp_spec_num5)/(4*TMath::Pi()*temp_Pm[binnum]*temp_Pm[binnum]));
			
	                /*test_Em.push_back(std::stod(tmp_spec_num1));
	                test_Em.push_back(std::stod(tmp_spec_num2));
	                test_Em.push_back(std::stod(tmp_spec_num3));
	                test_Em.push_back(std::stod(tmp_spec_num4));
	                test_Em.push_back(std::stod(tmp_spec_num5));
			*/
				
	          }
		  }//end of else 
		index++;
	  }//loop over all the lines in this file
	  std::cout<<"Looped over all the lines in a certain file"<<std::endl;
	  TGraph *gr_Em_spectrum[200];
	  TGraph *gr_Pm_spectrum; //for whole range - integral over all the Em
						
	  for(int i=0; i<200; i++){
		double spec_Em_x[4000];
		double spec_Em_y[4000];
		for(int j=0; j<4000; j++){
			std::cout<<"i= "<<i<<" j=  "<<j<<"   "<<spec_Em_bin[i][j]<<"   "<<spec_Em_amp[i][j]<<std::endl;
			spec_Em_x[j]=spec_Em_bin[i][j];
			spec_Em_y[j]=spec_Em_amp[i][j];
		}
		gr_Em_spectrum[i]=new TGraph(4000, spec_Em_x,spec_Em_y);
		std::string tempname="gr_Em_spectrum_"+to_string(i);
		gr_Em_spectrum[i]->SetName(tempname.c_str());
	  }
	
 	  std::string outfilename="demo_test_"+orbital[iorb]+"_"+COL[iorb][iw]+".root";
	  TFile ff(outfilename.c_str(), "recreate"); 
	  double spec_Pm_amp[200];
	  for(int ik=0; ik<200; ik++){
			gr_Em_spectrum[ik]->Write();	  
			spec_Pm_amp[ik]=gr_Em_spectrum[ik]->Integral();
			
	  }
	  gr_Pm_spectrum=new TGraph(200, temp_Pm, spec_Pm_amp);
	  gr_Pm_spectrum->SetName("gr_Pm_spectrum");
	  gr_Pm_spectrum->Write();
	  ff.Close();
	  
     }//end of loop over all the width of each orbital
 }//end of for loop



}
