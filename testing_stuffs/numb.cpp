#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <vector>

int main()
{
	struct window
	{
		size_t wid = 0,hei = 0;
		size_t pos_x = 0,pos_y = 0;
	};
	window wiin  = {0,0,0,0};
	window wiin0  = {0,0,0,0};
	window wiin1  = {0,0,0,0};
	std::vector<window> windows(4,wiin);
	for (int i = 0; i <= 100;i++)
	{
		int term_cols = i,term_rows = 30;
		//screen_get_dim(&term_cols,&term_rows);

		int padding = windows.size()-1;
		float tmp_wid = ((float)(term_cols-padding))/windows.size();
		int leftover = term_cols-padding-(ceil(tmp_wid)+((windows.size()-1)*floor(tmp_wid)));

		windows[0].wid = std::ceil(tmp_wid);
		windows[0].hei = term_rows-1; 
		windows[0].pos_x = 0;
		windows[0].pos_y = 0;
		size_t compund_wid = windows[0].wid+1;
		//size_t compund_hei = windows[0].hei;
		for(size_t idx = 1; idx < windows.size();++idx)
		{
			if(leftover > 0)
			{
				windows[idx].wid = std::floor(tmp_wid)+1;
				leftover--;
			}
			else
			{
				windows[idx].wid = std::floor(tmp_wid);
			}
			windows[idx].hei = term_rows-1; 
			windows[idx].pos_x = compund_wid;
			windows[idx].pos_y = 0;
			compund_wid += windows[idx].wid+1;
			//compund_hei += windows[idx].hei;
		}
		int total_wid = 0;
		for(window win : windows)
		{
			total_wid += win.wid;
	    }
		if(1/*(total_wid+padding)!=i*/)
		{
			printf("%i\tleftover:%i\n",i,leftover);
			for(window win : windows)
			{
				printf("wid:%lu hei:%lu pos_x:%lu pos_y:%lu\n",win.wid,win.hei,win.pos_x,win.pos_y);
			}
		}
	}
	return 0;
}
