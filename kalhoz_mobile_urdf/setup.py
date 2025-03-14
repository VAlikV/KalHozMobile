from setuptools import find_packages, setup
import os
from glob import glob

package_name = 'kalhoz_mobile_urdf'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name + '/models/', ['models/KalHozMobile.urdf']),
        ('share/' + package_name + '/meshes/', ['meshes/imu.STL']),
        ('share/' + package_name + '/meshes/', ['meshes/base_link.STL']),
        ('share/' + package_name + '/meshes/', ['meshes/left_wheel.STL']),
        ('share/' + package_name + '/meshes/', ['meshes/right_wheel.STL']),
        ('share/' + package_name + '/meshes/', ['meshes/lidar.STL']),
        ('share/' + package_name + '/rviz/', ['rviz/urdf.rviz']),
        (os.path.join('share', package_name, 'launch'), glob(os.path.join('launch', '*launch.[pxy][yma]*'))),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='gleb',
    maintainer_email='stojko.g@yandex.ru',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
        
        ],
    },
)

