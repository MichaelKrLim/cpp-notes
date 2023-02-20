To read in a varable input for a variety of different input cases : 

std::istream & operator >> (std::istream & in, join & name)
{
   if(std::isdigit(in.peek()))
   {
      in >> name.place;
      in >> name.character;
   }
   else
   {
      in >> name.character;
      in >> name.place;
   }
   if(!in.eof() && in.peek() == '-')
   {
    char t;
    in >> t;
   }
   return in;
}

 std::vector<join> answer(std::istream_iterator<join>{std::cin},{});
 
---------------------------------------------------------------------

you may use copy to a vecor's output stream to output
   
std::copy(answer.begin(),answer.end(),std::ostream_iterator<join>{std::cout});

---------------------------------------------------------------------
   
accumulate can sum values from two iterators, the type is determined based on the last parameter of accumulate  
                                                                                  vv
long long sum_e = std::accumulate(std::istream_iterator<long long> {stream}, {}, 0ll);

---------------------------------------------------------------------
   
conversion between bases:


digits = ////
   
int base = out == "dec" ? 10 : out == "hex" ? 16 : 2;
            std::string output;
            do 
            { 
                output += digits[dec % base];
                dec /= base;
            } while (dec > 0);



output must be big enough to store converted value:


output.resize(1000);
std::to_chars(&output[0], &output[output.size()], dec, base);

----------------------------------------------------------------------
