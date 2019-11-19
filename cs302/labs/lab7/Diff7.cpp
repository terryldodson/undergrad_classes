#include ... all needed header files

class matrix {
  // see handout from class or make your own
};

class LCS {
  public:
    void text1_push_back(...);
    void text2_push_back(...);
	void compute_alignment();
	void report_difference();

  private:
	// support functions
    // text1 buffer
    // text2 buffer
};

int main(int argc, char *argv[])
{
  // check two input files are specified on command line

  LCS lcs;  // instantiate your "LCS based diff" object

  // read the text from file1 into the lcs.text1 buffer
  // read the text from file2 into the lcs.text2 buffer

  lcs.compute_alignment();
  lcs.report_difference();
}
