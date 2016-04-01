#include <systemc>
using namespace sc_core; 

class A: public sc_module
{
public:
	SC_HAS_PROCESS( A );
	A( sc_module_name n ): sc_module( n )
  {
    exp( sig ); 

    tf = sc_create_vcd_trace_file( "tf" ); 
    sc_trace( tf, (DCAST<const sc_signal_in_if<int>*>( exp.get_interface() ))->read(), "exp" ); 
    
    SC_THREAD( run ); 
    
  }

  ~A()
  {
    sc_close_vcd_trace_file( tf ); 
  }

  void run()
  {
    sig.write( 0 ); 
    wait( 1, SC_NS ); 
    sig.write( 1 ); 
    wait( 1, SC_NS ); 
    sig.write( 2 ); 
    sc_stop();
  }
  
  sc_export<sc_signal_inout_if<int> > exp; 
private:
  sc_signal<int> sig; 
  sc_trace_file * tf;
};

int sc_main(int argc, char* argv[])
{
  A a("a"); 

  sc_start(); 

  return 0; 
}
