#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/netanim-module.h"
#include "ns3/mobility-module.h"
#include <cmath>

using namespace ns3;

int main ()
{
  NodeContainer nodes;
  nodes.Create (18);

  InternetStackHelper stack;
  stack.Install (nodes);

  PointToPointHelper p2p;
  p2p.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));

  // Create ring connections
  for (int i = 0; i < 18; i++)
  {
    p2p.Install (nodes.Get(i), nodes.Get((i+1)%18));
  }

  // Mobility
  MobilityHelper mobility;
  mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
  mobility.Install(nodes);

  AnimationInterface anim("ring18.xml");

  // Arrange in perfect circle
  double radius = 40;
  double centerX = 50;
  double centerY = 50;

  for (int i = 0; i < 18; i++)
  {
    double angle = i * (360.0 / 18);
    double x = centerX + radius * cos(angle * M_PI / 180);
    double y = centerY + radius * sin(angle * M_PI / 180);
    anim.SetConstantPosition(nodes.Get(i), x, y);
  }

  Simulator::Stop (Seconds(5));
  Simulator::Run ();
  Simulator::Destroy ();
}

