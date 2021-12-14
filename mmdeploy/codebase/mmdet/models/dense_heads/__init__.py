# Copyright (c) OpenMMLab. All rights reserved.
from .anchor_head import anchor_head__get_bboxes__ncnn
from .base_dense_head import base_dense_head__get_bbox
from .fcos_head import fcos_head__get_bboxes__ncnn
from .fovea_head import fovea_head__get_bboxes
from .rpn_head import rpn_head__get_bboxes, rpn_head__get_bboxes__ncnn
from .yolo_head import yolov3_head__get_bboxes, yolov3_head__get_bboxes__ncnn
from .yolox_head import yolox_head__get_bboxes

__all__ = [
    'anchor_head__get_bboxes__ncnn', 'fcos_head__get_bboxes__ncnn',
    'rpn_head__get_bboxes', 'rpn_head__get_bboxes__ncnn',
    'yolov3_head__get_bboxes', 'yolov3_head__get_bboxes__ncnn',
    'yolox_head__get_bboxes', 'base_dense_head__get_bbox',
    'fovea_head__get_bboxes'
]