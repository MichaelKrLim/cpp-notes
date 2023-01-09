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
