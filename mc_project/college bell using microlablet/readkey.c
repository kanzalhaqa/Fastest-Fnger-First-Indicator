unsigned char key_value;
unsigned char readkey()
 {
while(1)
 {
      P2=0x7F;

			 if(P2==0x7B)
			 {key_value=0;
			 return key_value;}
		
			 
			 
			P2=0xBF;
			if(P2==0xB7)
			 {key_value=1;
			 return key_value;}
			 if(P2==0xBB)
			 {key_value=2;
			 return key_value;}
			 if(P2==0xBD)
			 {key_value=3;
			 return key_value;}
			 
			 
			P2=0xDF;
			 if(P2==0xD7)
			 {key_value=4;
			 return key_value;}
			if(P2==0xDB)
			 {key_value=5;
			 return key_value;} 
			 if(P2==0xDD)
			 {key_value=6;
			 return key_value;}
			 
			 
			P2=0xEF;
			 if(P2==0xE7)
			 {key_value=7;
			 return key_value;}
			 if(P2==0xEB)
			 {key_value=8;
			 return key_value;}
			 if(P2==0xED)
			 {key_value=9;
			 return key_value;}
    }
 } 