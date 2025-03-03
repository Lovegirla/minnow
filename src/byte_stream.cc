#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity )
  : capacity_( capacity ), bytes_pushed_( 0 ), bytes_popped_( 0 ), close_flag_( false )
{}

void Writer::push( string data )
{
  if ( has_error() || is_closed() ) {
    return;
  }
  const size_t len = min( data.length(), available_capacity() );
  // std::copy(data.begin(), data.begin() + len, std::back_inserter(data_));
  buf_.append( data.substr( 0, len ) );
  bytes_pushed_ += len;
}

void Writer::close()
{
  // Your code here.
  close_flag_ = true;
}

bool Writer::is_closed() const
{
  return close_flag_; // Your code here.
}

uint64_t Writer::available_capacity() const
{
  return capacity_ - ( bytes_pushed_ - bytes_popped_ ); // Your code here.
}

uint64_t Writer::bytes_pushed() const
{
  return bytes_pushed_; // Your code here.
}

string_view Reader::peek() const
{
  return this->buf_;
}

void Reader::pop( uint64_t len )
{
  if ( bytes_buffered() == 0 ) {
    return;
  }
  len = std::min( len, buf_.length() );
  buf_.erase( 0, len );
  bytes_popped_ += len;
}

bool Reader::is_finished() const
{
  return close_flag_ && bytes_buffered() == 0; // Your code here.
}

uint64_t Reader::bytes_buffered() const
{
  return bytes_pushed_ - bytes_popped_; // Your code here.
}

uint64_t Reader::bytes_popped() const
{
  return bytes_popped_; // Your code here.
}
