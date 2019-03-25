//
// Created by vant3d on 25/03/19.
//

#include <pluginlib/class_list_macros.h>
#include "compressed_image_transport/compressed_subscriber.h"
#include "compressed_image_transport/compressed_publisher.h"

PLUGINLIB_EXPORT_CLASS(compressed_image_transport::CompressedPublisher,
        image_transport::PublisherPlugin);
PLUGINLIB_EXPORT_CLASS(compressed_image_transport::CompressedSubscriber,
        image_transport::SubscriberPlugin);