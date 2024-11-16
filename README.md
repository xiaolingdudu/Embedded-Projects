
## Abstract
The requirements analysis of this project covers the functions, performance, technology and reliability of the smart home voice interaction system. The system uses voice recognition and network programming technology to control smart home devices, and users can remotely operate home devices through voice commands. In the implementation process, C language programming technology, Linux system hardware control interface, iFlytek voice recognition technology, and TCP/IP protocol will be used for client-server communication. By integrating multiple functional modules, it aims to provide a diverse smart home monitoring experience. The system not only has basic device control functions (such as unlocking and sensor data collection), but also supports entertainment functions (such as drawing board, Gobang, video playback, etc.). By integrating USB cameras and other hardware devices, the system can provide real-time monitoring and environmental monitoring while ensuring the real-time and stability of the system.
---z

## 💎Let's Get Started!
### `A. Installation`

Note that the code in this repo runs under **Linux** system. 

The repo is based on the [VMama repo](https://github.com/xiaolingdudu/Embedded-Projects), thus you need to install it first. The following installation sequence is taken from the VMamba repo. 

**Step 1: Clone the repository:**

Clone this repository and navigate to the project directory:
```bash
git clone https://github.com/xiaolingdudu/Embedded-Projects.git
cd Embedded-Projects
```


**Step 2: Environment Setup:**

It is recommended to set up a conda environment and installing dependencies via pip. Use the following commands to set up your environment:

***Create and activate a new conda environment***

```bash
conda create -n msmamba
conda activate msmamba
```

***Install dependencies***

```bash
pip install -r requirements.txt
cd kernels/selective_scan && pip install .
```

### `B. Data Preparation`

The five datasets [RPE](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC4760937/), [MHIST](https://bmirds.github.io/MHIST/) , [SARS](https://lhncbc.nlm.nih.gov/LHC-downloads/downloads.html#malaria-datasets) ,[TissueMnist](https://medmnist.com/) and [MedMf_colon](https://medfm2023.grand-challenge.org/medfm2023/) are used for MIC experiments. Please download them and make them have the following folder/file structure:
```
${DATASET_ROOT}   # Dataset root directory, for example: /home/username/data
├── RPE
    ├── train
    │   ├── class 1
    │   │   ├──00001.png
    │   │   ├──00002.png
    │   │   ├──00003.png
    │   │   ...
    │   │
    │   ├── class 2
    │   │   ├──00001.png
    │   │   ... 
    │   │
    │   └── class n
    │       ├──00001.png 
    │       ...   
    ├── val
    │   ├── ...
    ├── test
    │   ├── ...
    │   ...
├── MHIST
├── SARS
├── TissueMnist
├── MedMf_Colon
```
Or you can download it from here: [baidu Netdisk](https://pan.baidu.com/s/1VzCz9UOKg0hyZIjvUOR8kA?pwd=1314 )


### `C. Model Training`


```bash
python train.py 
```

### `D. Model Testing`
```bash
python test.py 
```
🐥: Before training and testing, configure the relevant parameters in the script



## 🤝Acknowledgments
This project is based on VMamba ([paper](https://arxiv.org/abs/2401.10166), [code](https://github.com/MzeroMiko/VMamba)). Thanks for their excellent works!!

## 🙋Q & A
***For any questions, please feel free to [contact us.](zs@stu.njau.edu.cn)***
## 📜Reference

If this code or paper contributes to your research, please kindly consider citing our paper and give this repo ⭐️ 🌝
```


```


