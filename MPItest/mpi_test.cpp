#include <pcl/ModelCoefficients.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/features/normal_3d.h>
#include <pcl/kdtree/kdtree.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/console/time.h>
#include <pcl/filters/passthrough.h>
#include <string>

#include <pcl/visualization/cloud_viewer.h>
#include <pcl/features/moment_of_inertia_estimation.h>
#include <vector>
#include <pcl/console/parse.h>

#include <iostream>
#include <mpi.h>

static int numprocs;

int main(int argc, char **argv) {
int my_rank;
// MPI initializations
MPI_Status status;
MPI_Init (&argc, &argv);
MPI_Comm_size (MPI_COMM_WORLD, &numprocs);
MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);

//************************************************************************************************************


if(my_rank == 0){ // I'm master and handle the splitting

  // Timer object
  pcl::console::TicToc tt;
  
  pcl::PCDReader reader;
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_f (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_main (new pcl::PointCloud<pcl::PointXYZ>);

  reader.read ("../../PCDdataFiles/data02.pcd", *cloud);
  std::cout << "PointCloud before filtering has: " << cloud->points.size () << " data points." << std::endl; //*





  pcl::PointCloud<pcl::PointXYZ> cloud_yo;


  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud0 (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud1 (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud2 (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud3 (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud4 (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud5 (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud6 (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud7 (new pcl::PointCloud<pcl::PointXYZ>);

  std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr > v;
  v.push_back(cloud0);
  v.push_back(cloud1);
  v.push_back(cloud2);
  v.push_back(cloud3);
  v.push_back(cloud4);
  v.push_back(cloud5);
  v.push_back(cloud6);
  v.push_back(cloud7);

  // Devide the dataset and keep every n:th point (setting it to 1 will include all points)

  tt.tic();

  int m_tag = 0; // MPI message tag
  float buff0 [20000];
  float buff1 [20000];
  float buff2 [20000];
  float buff3 [20000];
  float buff4 [20000];
  float buff5 [20000];
  float buff6 [20000];
  float buff7 [20000];
  short count0,count1,count2,count3,count4,count5,count6,count7 = -1;

  int nth_point = 3;
  double zero = 0.0000000;
  for (int iii = 0; iii < static_cast<int> (cloud->size ()); ++iii){ 
    if((iii%nth_point) == 0){
    	if(cloud->points[iii].x > zero){
	          if(cloud->points[iii].y > zero){
	              if(cloud->points[iii].y > cloud->points[iii].x){
	              	  buff0[++count0] = cloud->points[iii].x;
	              	  buff0[++count0] = cloud->points[iii].y;
	              	  buff0[++count0] = cloud->points[iii].z;
	              }else{
	                  buff1[++count1] = cloud->points[iii].x;
	              	  buff1[++count1] = cloud->points[iii].y;
	              	  buff1[++count1] = cloud->points[iii].z;
	              }
	          }else{
	              if((abs(cloud->points[iii].y)) > cloud->points[iii].x){
	                  buff2[++count2] = cloud->points[iii].x;
	              	  buff2[++count2] = cloud->points[iii].y;
	              	  buff2[++count2] = cloud->points[iii].z;
	              }else{
	                  buff4[++count3] = cloud->points[iii].x;
	              	  buff4[++count3] = cloud->points[iii].y;
	              	  buff4[++count3] = cloud->points[iii].z;
	              }
	          }    
	      }else{
	          if(cloud->points[iii].y > zero){
	              if(cloud->points[iii].y > (abs(cloud->points[iii].x))){
	              	  buff4[++count4] = cloud->points[iii].x;
	              	  buff4[++count4] = cloud->points[iii].y;
	              	  buff4[++count4] = cloud->points[iii].z;
	               }else{
	                  buff5[++count5] = cloud->points[iii].x;
	              	  buff5[++count5] = cloud->points[iii].y;
	              	  buff5[++count5] = cloud->points[iii].z;
	               }
	           }else{
	               if(cloud->points[iii].y > cloud->points[iii].x){
	                  buff6[++count6] = cloud->points[iii].x;
	              	  buff6[++count6] = cloud->points[iii].y;
	              	  buff6[++count6] = cloud->points[iii].z;
	                }else{
	                  buff7[++count7] = cloud->points[iii].x;
	              	  buff7[++count7] = cloud->points[iii].y;
	              	  buff7[++count7] = cloud->points[iii].z;
	                }
	          }
	      }
    }else{
    	//Ignore this point
    }
  }

   count0++; // This is needed because of the 0-index array

   cout << "Splitting data in: " << tt.toc() << " ms" << endl;
   tt.tic();
   // Send the number of floats to send
   MPI_Send(&count0, 1, MPI_INT, 1, m_tag, MPI_COMM_WORLD);
   // Send the float buffer (first sector)
   MPI_Send(&buff0, count0, MPI_FLOAT, 1, m_tag, MPI_COMM_WORLD);

   cout << "Sending data in: " << tt.toc() << " ms" << endl;
   

}else if(my_rank == 1){ // Worker1 runs this code

	pcl::console::TicToc tt;
	tt.tic();

	int count;

	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);

 	float buff [20000];
 
    MPI_Recv(&count, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

 	MPI_Recv(&buff, count, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

 	
 	//cloud->points.push_back(pcl::PointXYZ (buff[0], buff[1], buff[2]));

 	cout << "------------ worker1 -------------------" << endl;
	cout << "Count is: " << count  << " count/3 = " << (count/3) << endl;
 	cout << "Received: " << cloud->points.size() << " points." << endl;
 	cout << "Time elapsed: " << tt.toc() << "ms" << endl;
}




//*****************************************************************************************************************
// Get the name of the processor
char processor_name[MPI_MAX_PROCESSOR_NAME];
int name_len;
MPI_Get_processor_name(processor_name, &name_len);

// Print off a hello world message
//printf("Hello world from processor %s ", processor_name);

//double time_start = MPI_Wtime();
//std::cout << "Hello World, my rank is " << my_rank <<" "<< MPI_Wtime() - time_start << std::endl;
// End MPI
MPI_Finalize ();
return 0;
}