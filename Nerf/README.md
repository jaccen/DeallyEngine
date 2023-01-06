# 神经渲染相关

CVPR 2022的论文：
https://arxiv.org/search/?query=cvpr+2022&searchtype=all&abstracts=hide&order=-announced_date_first&size=50

CVPR 2022中与NeRF相关的论文（1、Mip-NeRF; 2、Point-NeRF; 3、Human-NeRF; 4、Urban-NeRF; 5、Block-NeRF; 6、Raw-NeRF）。

NeRF 是 2020 年 ECCV 上获得最佳论文荣誉提名的工作，其影响力是十分巨大的。NeRF 将隐式表达推上了一个新的高度，仅用 2D 的 posed images 作为监督，即可表示复杂的三维场景，在新视角合成这一任务上的表现是非常 impressive 的。

# 1、Mip-NeRF 360 （谷歌、哈佛大学）
简介
NeRF在小范围内渲染效果尚好，但它们在 "无界 "场景中却举步维艰。在这种情况下，原有的NeRF的模型往往会产生模糊或低分辨率的渲染，可能会表现出伪影。本文提出了 "mip-NeRF 360"（改进了mip-NeRF），它使用非线性场景参数化、在线蒸馏和一种新型的基于失真的正则器来克服无边界场景带来的挑战。与mip-NeRF相比，MSE减少了54%，并且能够为高度复杂、无边界的真实世界场景产生真实的合成视图和精准的深度图。
项目地址：
Mip-NeRF 360: Unbounded Anti-Aliased Neural Radiance Fields
​jonbarron.info/mipnerf360/

论文链接：arxiv.org/abs/2111.12077


# 2、Point-NeRF（南加州大学、Adobe研究院）
简介
像 NeRF 这样的体积神经渲染方法会生成高质量的视图合成结果，但会针对每个场景进行优化，从而导致重建时间过长。另一方面，深度多视图立体方法可以通过直接网络推理快速重建场景几何。Point-NeRF 结合了这两种方法的优点，通过使用具有相关神经特征的神经 3D 点云来模拟辐射场。Point-NeRF 可以通过在基于光线行进的渲染管道中聚合场景表面附近的神经点特征来有效地渲染。此外，Point-NeRF 可以通过直接推断预训练的深度网络来初始化，以生成神经点云；这个点云可以被微调以超过 NeRF 的视觉质量，训练时间快 30 倍。
项目地址：
Point-NeRF
​xharlie.github.io/projects/project_sites/pointnerf/index.html
论文链接：https://arxiv.org/pdf/2201.08845.pdf


# 3、Human NeRF （华盛顿大学、谷歌）
简介
介绍了一种自由视点渲染方法——HumanNeRF——它适用于人类执行复杂身体运动的给定单目视频，例如来自 YouTube 的视频。其可以在任何帧暂停视频并从任意新的摄像机视点甚至是针对该特定帧和身体姿势的完整 360 度摄像机路径渲染主体。这项任务特别具有挑战性，因为它需要合成身体的逼真细节，从输入视频中可能不存在的各种摄像机角度看，以及合成精细的细节，如布料褶皱和面部外观。该方法优化了典型 T 姿势中人的体积表示，与运动场相一致，该运动场通过向后扭曲将估计的规范表示映射到视频的每一帧。运动场被分解为由深度网络产生的骨骼刚性和非刚性运动。论文展示了与先前工作相比的显着性能改进，以及在具有挑战性的不受控制的捕获场景中移动人类的单目视频的自由视点渲染示例。

项目地址：
HumanNeRF: Free-viewpoint Rendering of Moving People from Monocular Video
​grail.cs.washington.edu/projects/humannerf/
论文链接：https://arxiv.org/abs/2201.04127

# 4、Urban NeRF（谷歌）
简介
这项工作的目标是从扫描平台捕获的数据中执行 3D 重建和新颖的视图合成，这些平台通常用于城市户外环境（例如街景）中的世界地图绘制。给定一系列由相机和扫描仪在户外场景中移动获得的 RGB 姿势图像和激光雷达扫描，其生成了一个模型，可以从中提取 3D 表面并合成新的 RGB 图像。论文扩展了神经辐射场，该方法已被证明可以在受控环境中为小场景合成逼真的新颖图像，以及利用异步捕获的激光雷达数据的新方法，以解决捕获图像之间的曝光变化，以及利用预测的图像分割来监督指向天空的光线的密度。这三个扩展中的每一个都在街景数据的实验中提供了显着的性能改进。与传统方法（例如~COLMAP）和最近的神经表示（例如~Mip-NeRF,也就是上面的第一篇论文）相比，该系统产生最先进的 3D 表面重建并合成更高质量的新视图。

项目地址：
https://urban-radiance-fields.github.io/
​urban-radiance-fields.github.io/
论文链接：https://arxiv.org/abs/2111.14643

# 5、Block-NeRF（UC伯克利，Waymo，谷歌）
简介
作者提出了 Block-NeRF，一种可以表示大规模环境的神经辐射场的变体。具体来说，其证明，当缩放 NeRF 以渲染跨越多个街区的城市规模场景时，将场景分解为单独训练的 NeRF 至关重要。这种分解将渲染时间与场景大小分离，使渲染能够扩展到任意大的环境，并允许对环境进行逐块更新。论文采用了几项架构更改，以使 NeRF 对在不同环境条件下数月捕获的数据具有鲁棒性。其为每个单独的 NeRF 添加了外观嵌入、学习姿势细化和可控曝光，并引入了一种用于对齐相邻 NeRF 之间外观的程序，以便它们可以无缝组合。论文从 280 万张图像中构建了一个 Block-NeRF 网格，以创建迄今为止最大的神经场景表示，能够渲染旧金山的整个社区。
项目地址：
Block-NeRF
​waymo.com/intl/zh-cn/research/block-nerf/

论文链接：https://arxiv.org/abs/2202.05263


# 6、Raw NeRF（谷歌）
简介
神经辐射场 (NeRF) 是一种从姿势输入图像的集合中合成高质量新视图的技术。与大多数视图合成方法一样，NeRF 使用色调映射低动态范围（LDR）作为输入；这些图像已由有损相机管道处理，该管道可以平滑细节、剪辑高光并扭曲原始传感器数据的简单噪声分布。作者将 NeRF 修改为直接在线性原始图像上进行训练，保留场景的完整动态范围。通过从生成的 NeRF 渲染原始输出图像，其可以执行新颖的高动态范围 (HDR) 视图合成任务。除了改变相机视角之外，还可以在事后操纵焦点、曝光和色调映射。尽管单个原始图像看起来比经过后处理的图像噪声大得多，论文证明了 NeRF 对原始噪声的零均值分布具有高度鲁棒性。当针对许多嘈杂的原始输入 (25-200) 进行优化时，NeRF 生成的场景表示非常准确，以至于其渲染的新颖视图优于在相同宽基线输入图像上运行的专用单图像和多图像深度原始降噪器。RawNeRF可以从在近黑暗中捕获的极其嘈杂的图像中重建场景。

项目地址：
NeRF in the Dark (RawNeRF)
​bmild.github.io/rawnerf/index.html

论文链接：https://arxiv.org/abs/2111.13679

# 7、人脸重建

#nerf人脸重建：
1、MobileR2L算法论文(论文链接参考)，
https://snap-research.github.io/MobileR2L/

2、将RAD-nerf中的语音提取模型从deepspeech替换为wav2vec 2模型，在40s左右的训练视频上，效果和deepspeech类似，对于中文的驱动效果不是很好。使用更长的训练视频（2~3分钟），wav2vec2的语音驱动效果更好，推理速度V100上15~20fps。使用3DMM表情系数驱动RAD-nerf，驱动结果嘴型抖动较大，效果相对nerfblendshape略差

3、rad-nerf，语音驱动的nerf人脸重建算法，该算法能实现V100上20fps的推理速度，且驱动效果较好。问题是目前由于容器无法联网，只能使用较早版本的deepspeech提取语音特征，可能影响语音特征提取的效果。

4、hyper-nerf算法，将表情系数与hyper-nerf结合，数据集上实验效果相比nerfblendshape略差，比基于instant-ngp的baseline算法略好

5、基于Mesh人脸重建
      腾讯hifi3d算法：配置环境，用论文中数据集跑通代码流程，运行了人脸重建，基本达到论文中所提效果
      基于instant-ngp和blendshape表情系数的人脸重建算法，并进行若干改进调优：基于概率的光线采样，表情系数采用3DDFA生成，基于感知的patch loss，cuda ray加速等，在实验数据集上效果和速度得到一定提升
      

